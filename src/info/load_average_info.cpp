#include "load_average_info.h"
#include <fstream>
#include <iostream>
#include <ncurses.h>

using namespace std;


LoadAverageInfo get_load_average() {
  // open the file and error check
  ifstream loadavg_file(PROC_ROOT "/loadavg");
  if (!loadavg_file) {
    cerr << "Unable to read from /proc/loadavg" << endl;
    endwin();
    exit(EXIT_FAILURE);
  }

  // declare initial LoadAverageInfo struct
  LoadAverageInfo info;

  // put the data into the correct variables in the struct
  loadavg_file
    >> info.one_min
    >> info.five_mins
    >> info.fifteen_mins;

  loadavg_file.close();

  return info;
}
