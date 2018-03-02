#include "display.h"
#include "conversions.h"

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
  printw("uptime: %s", human_readable_time(info.uptime).c_str());
}

void print_load_average(const SystemInfo& info) {
  LoadAverageInfo ave = info.load_average;
  printw("   load average: %.2f, %.2f, %.2f", ave.one_min, ave.five_mins, ave.fifteen_mins);
}
