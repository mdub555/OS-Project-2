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

void print_processors(std::vector<CpuInfo>& prev, std::vector<CpuInfo>& curr);

void print_num_processes(const SystemInfo& info);

void print_memory(const MemoryInfo& mem);

void print_processes(std::vector<ProcessInfo>& info);

double get_cpu_percent_user(const CpuInfo& cpu);
double get_cpu_percent_kernel(const CpuInfo& cpu);
double get_cpu_percent_idle(const CpuInfo& cpu);
