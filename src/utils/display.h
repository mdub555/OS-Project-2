#include "../info/system_info.h"
#include <ncurses.h>
#include <vector>

/** Makes a progress bar starting at the current cursor position and ending
 *  at the end of the line.
 *  @arg fraction the fraction of the progress desired to display
 */
void progressBar(const std::vector<double>& fraction);

void print_uptime(const SystemInfo& info);

void print_load_average(const LoadAverageInfo& ave);

void print_processors(std::vector<CpuInfo>& cpus);

void print_num_processes(const SystemInfo& info);

void print_memory(const MemoryInfo& mem);

void print_processes(std::vector<ProcessInfo>& info);
