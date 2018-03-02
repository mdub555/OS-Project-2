#include "../info/system_info.h"
#include <ncurses.h>

/** Makes a progress bar starting at the current cursor position and ending
 *  at the end of the line.
 *  @arg fraction the fraction of the progress desired to display
 */
void progressBar(double fraction);

void print_uptime(const SystemInfo& info);
