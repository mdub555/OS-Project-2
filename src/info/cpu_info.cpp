#include "cpu_info.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


vector<CpuInfo> get_cpu_info() {
  // open the stat file and check for errors
  ifstream stat_file(PROC_ROOT "/stat");
  if (!stat_file) {
    cerr << "Unable to read from /proc/stat" << endl;
    exit(EXIT_FAILURE);
  }

  vector<CpuInfo> all_cpus;                 // declare vector

  string label;                             // for the first value in a line of /proc/stat
  while (true) {
    stat_file >> label;                     // get the label for this line
    if (label.substr(0, 3) != "cpu") break; // break if this line isn't for a cpu
    CpuInfo info;                           // declare initial CpuInfo variable
    stat_file                               // input the data into the correct variables
      >> info.user_time
      >> info.nice_time
      >> info.system_time
      >> info.idle_time
      >> info.io_wait_time
      >> info.irq_time
      >> info.softirq_time
      >> info.steal_time
      >> info.guest_time
      >> info.guest_nice_time;

    all_cpus.push_back(info);               // add it to the vector
  }

  stat_file.close();

  return all_cpus;
}


CpuInfo operator -(const CpuInfo& lhs, const CpuInfo& rhs) {
  CpuInfo diff;
  diff.user_time = lhs.user_time - rhs.user_time;
  diff.nice_time = lhs.nice_time - rhs.nice_time;
  diff.system_time = lhs.system_time - rhs.system_time;
  diff.idle_time = lhs.idle_time - rhs.idle_time;
  diff.io_wait_time = lhs.io_wait_time - rhs.io_wait_time;
  diff.irq_time = lhs.irq_time - rhs.irq_time;
  diff.softirq_time = lhs.softirq_time - rhs.softirq_time;
  diff.steal_time = lhs.steal_time - rhs.steal_time;
  diff.guest_time = lhs.guest_time - rhs.guest_time;
  diff.guest_nice_time = lhs.guest_nice_time - rhs.guest_nice_time;
  return diff;
}
