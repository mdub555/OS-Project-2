#include "process_info.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;


ProcessInfo get_process(int pid, const char* basedir) {
  ProcessInfo process;
  string process_file_name = (string)basedir + "/" + to_string(pid);

  ///////////////////////////////////////
  // get all info from the `stat` file //
  ///////////////////////////////////////
  string stat_file_name = process_file_name + "/stat";
  ifstream stat_file(stat_file_name.c_str());
  if (!stat_file) {
    cerr << "Unable to read from " << stat_file_name << endl;
    return ProcessInfo();
  }

  stat_file
    >> process.pid
    >> process.comm
    >> process.state
    >> process.ppid
    >> process.pgrp
    >> process.session
    >> process.tty_nr
    >> process.tpgid
    >> process.flags
    >> process.minflt
    >> process.cminflt
    >> process.majflt
    >> process.cmajflt
    >> process.utime
    >> process.stime
    >> process.cutime
    >> process.cstime
    >> process.priority
    >> process.nice
    >> process.num_threads
    >> process.itrealvalue
    >> process.starttime
    >> process.vsize
    >> process.rss
    >> process.rsslim
    >> process.startcode
    >> process.endcode
    >> process.startstack
    >> process.kstkesp
    >> process.kstkeip
    >> process.signal
    >> process.blocked
    >> process.sigignore
    >> process.sigcatch
    >> process.wchan
    >> process.nswap
    >> process.cnswap
    >> process.exit_signal
    >> process.processor
    >> process.rt_priority
    >> process.policy
    >> process.delayacct_blkio_ticks
    >> process.guest_time
    >> process.cguest_time;

  stat_file.close();


  ////////////////////////////////////////
  // get all info from the `statm` file //
  ////////////////////////////////////////
  string statm_file_name = process_file_name + "/statm";
  ifstream statm_file(statm_file_name.c_str());
  if (!statm_file) {
    cerr << "Unable to read from " << statm_file_name << endl;
    return ProcessInfo();
  }

  statm_file
    >> process.size
    >> process.resident
    >> process.share
    >> process.trs
    >> process.lrs
    >> process.drs
    >> process.dt;

  statm_file.close();


  ///////////////////////////
  // get command line call //
  ///////////////////////////
  string cmdline_file_name = process_file_name + "/cmdline";
  ifstream cmdline_file(cmdline_file_name.c_str());
  if (!cmdline_file) {
    cerr << "Unable to read from " << cmdline_file_name << endl;
    return ProcessInfo();
  }

  cmdline_file >> process.command_line;

  cmdline_file.close();

  // remove last character from the string, since it will always be '\0'
  process.command_line = process.command_line.substr(0, process.command_line.size()-1);
  // replace the '\0' characters
  for (char& c : process.command_line) {
    if (c == '\0') c = ' ';
  }
  // if the command is empty, use the `comm` file as default
  if (process.command_line == "") {
    string comm_file_name = process_file_name + "/comm";
    ifstream comm_file(comm_file_name.c_str());
    if (!comm_file) {
      cerr << "Unable to read from " << comm_file_name << endl;
      return ProcessInfo();
    }
    comm_file >> process.command_line;

    comm_file.close();
  }

  
  //////////////
  // get tgid //
  //////////////
  string status_file_name = process_file_name + "/status";
  ifstream status_file(status_file_name.c_str());
  if (!status_file) {
    cerr << "Unable to read from " << status_file_name << endl;
    return ProcessInfo();
  }
  string label;
  while (true) {
    status_file >> label;
    if (label == "Tgid:") {
      status_file >> process.tgid;
      break;
    }
  }

  status_file.close();


  /////////////////////
  // get all threads //
  /////////////////////
  string thread_dir = process_file_name + "/task";
  // check if the threads file exists first, then get them all
  if (!access(thread_dir.c_str(), F_OK) ) {
    process.threads = get_all_processes(thread_dir.c_str());
  }

  return process;
}


// this process will be called from a function which it itself calls, so in order to prevent an
// infinite loop, there needs to be a base case which stops is from occurring. This happens when
// the basedir has no files whose names are numbers, in which case get_process() is never called.
vector<ProcessInfo> get_all_processes(const char* basedir) {
  vector<ProcessInfo> processes;

  DIR *dirp;
  struct dirent *directory;
  dirp = opendir(basedir);
  if (dirp) {
    // loop through all directories in basedir
    while ((directory = readdir(dirp)) != NULL) {
      // check if the directory is a number
      if (((string)directory->d_name).find_first_not_of( "0123456789" ) != string::npos) {
        continue;
      }
      // get the process info for this pid
      ProcessInfo temp = get_process(atoi(directory->d_name), basedir);
      processes.push_back(temp);
    }
    if (closedir(dirp) != 0) {
      perror(basedir);
      exit(errno);
    }
  } else {
    perror(basedir);
    exit(errno);
  }

  return processes;
}
