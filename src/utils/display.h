#include "../info/system_info.h"
#include <ncurses.h>
#include <vector>

/** Makes a progress bar starting at the current cursor position and ending
 *  at the end of the line.
 *  @arg fraction the fraction of the progress desired to display
 */
void progressBar(const std::vector<double>& fraction);

void print_uptime(const SystemInfo& info);

void print_load_average(const SystemInfo& info);

void print_processors(const SystemInfo& info);

void print_num_processes(const SystemInfo& info);
