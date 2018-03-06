#include "display.h"
#include "conversions.h"
#include <algorithm>
#include <unistd.h>


void progressBar(double fraction) {
  // starting position of the bar
  int start = getcurx(stdscr)+1;
  // total number of columns for the bar (leave space for the newline
  int total = COLS - start - 2;
  // get total number of columns that will be filled in
  int progress = total * fraction;
  addch('[');
  for (int i = 0; i < progress; i++) {
    addch(ACS_CKBOARD);
  }
  for (int i = progress; i < total; i++) {
    addch(' ');
  }
  addch(']');
  addch('\n');
}


void print_uptime(const SystemInfo& info) {
  printw("Uptime: %s", human_readable_time(info.uptime).c_str());
}


void print_load_average(const LoadAverageInfo& ave) {
  printw("   Load Average: %.2f, %.2f, %.2f\n", ave.one_min, ave.five_mins, ave.fifteen_mins);
}


void print_processors(std::vector<CpuInfo>& cpus) {
  printw("      |   user mode   |  kernel mode  |    idling\n");
  for (CpuInfo& cpu : cpus) {
    printw("  cpu | %13s | %13s | %13s\n",
            human_readable_time(cpu.user_time).c_str(),
            human_readable_time(cpu.system_time).c_str(),
            human_readable_time(cpu.idle_time).c_str());
  }
}


void print_num_processes(const SystemInfo& info) {
  printw("Processes: %i total, %i running", info.num_processes, info.num_running);
  printw("  Threads: %i user, %i kernel\n", info.num_user_threads, info.num_kernel_threads);
}


void print_memory(const MemoryInfo& mem) {
  unsigned long long used = mem.total_memory - mem.free_memory;
  printw("Mem: %s used + %s free / %s total\n",
         human_readable_memory(used).c_str(),
         human_readable_memory(mem.free_memory).c_str(),
         human_readable_memory(mem.total_memory).c_str());
}


void print_processes(std::vector<ProcessInfo>& proc) {
  std::string title_row = "  PID |   Res   | S | CPU\% |   Time   | Command\n";
  printw(title_row.c_str());
  int rows = LINES - getcury(stdscr);
  int cmd_cols = COLS - (title_row.size()-7);
  for (int i = 0; i < rows; i++) {
    unsigned long time = (proc[i].utime + proc[i].stime) / sysconf(_SC_CLK_TCK);
    std::string res = human_readable_memory(proc[i].rss * sysconf(_SC_PAGESIZE) / 1024);
    printw("%5i |%8s | %c |  %2.1f | %s | %.*s\n",
          proc[i].pid, res.c_str(), proc[i].state,
          proc[i].cpu_percent,
          human_readable_time(time).c_str(),
          cmd_cols, proc[i].command_line.c_str());
  }
}
