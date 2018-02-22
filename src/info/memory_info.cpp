#include "memory_info.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <ncurses.h>
#include <sstream>

using namespace std;


MemoryInfo get_memory_info() {
  // make initial struct
  MemoryInfo info;

  // open the file
  ifstream meminfo_file(PROC_ROOT "/meminfo");
  string line, name;  // declare the line and name associated that line
  if (meminfo_file) { // check if the file opened correctly
    while (getline(meminfo_file, line)) {
      istringstream linestream(line);       // turn the line into an istringstream
      linestream >> name;                   // populate the name of the line
      name = name.substr(0, name.size()-1); // remove the trailing `:`

      // depending on the name of the line, add the data to the correct variable
      if (name == "MemTotal") {
        linestream >> info.total_memory;
      } else if (name == "MemFree") {
        linestream >> info.free_memory;
      } else if (name == "Buffers") {
        linestream >> info.buffers_memory;
      } else if (name == "Cached") {
        linestream >> info.cached_memory;
      } else if (name == "SwapTotal") {
        linestream >> info.total_swap;
      } else if (name == "SwapFree") {
        linestream >> info.free_swap;
      }

    }
    meminfo_file.close();
  } else {
    cerr << "Unable to open /proc/meminfo" << endl;
    exit(EXIT_FAILURE);
  }
  return info;
}
