#include "system_info.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

using namespace std;


double get_uptime() {
  ifstream uptime_file(PROC_ROOT "/uptime");
  if (!uptime_file) {
    cerr << "Unable to read from /proc/uptime" << endl;
    endwin();
    exit(EXIT_FAILURE);
  }
  double uptime;
  uptime_file >> uptime;
  uptime_file.close();
  return uptime;
}


SystemInfo get_system_info() {
  SystemInfo system;

  system.uptime = get_uptime();

  system.load_average = get_load_average();

  system.memory_info = get_memory_info();

  system.cpus = get_cpu_info();

  system.processes = get_all_processes(PROC_ROOT);

  system.num_processes = system.processes.size();

  system.num_threads = 0;
  system.num_user_threads = 0;
  system.num_kernel_threads = 0;
  system.num_running = 0;
  for (ProcessInfo proc : system.processes) {
    // check if process is running
    if (proc.state == 'R') system.num_running++;
    // check all threads for type
    if (proc.is_kernel_thread()) system.num_kernel_threads++; // kernel threads only at top level
    for (ProcessInfo thread : proc.threads) {
      if (thread.is_user_thread()) system.num_user_threads++; // user threads never in top level
    }
  }
  system.num_threads = system.num_kernel_threads + system.num_user_threads;

  return system;
}
