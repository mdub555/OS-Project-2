#include "load_average_info.h"
#include <fstream>
#include <iostream>

using namespace std;


LoadAverageInfo get_load_average() {
  // TODO: implement me
  ifstream loadavg_file(PROC_ROOT "/loadavg");

  if (!loadavg_file) {
    cerr << "Unable to read from /proc/loadavg" << endl;
    exit(EXIT_FAILURE);
  }

  LoadAverageInfo info;

  loadavg_file
    >> info.one_min
    >> info.five_mins
    >> info.fifteen_mins;
  return info;
}
