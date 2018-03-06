/**
 * Contains the main() routine of what will eventually be your version of top.
 */

#include "info/cpu_info.h"
#include "info/system_info.h"
#include "utils/display.h"
#include "utils/compare.h"
#include "utils/flags.h"
#include <cstdlib>
#include <ncurses.h>
#include <algorithm>

using namespace std;


void update_cpu_percent(SystemInfo& previous, SystemInfo& current);


/**
 * Gets a character from the user, waiting for however many milliseconds that
 * were passed to timeout() below. If the letter entered is q, this method will
 * exit the program.
 */
void exit_if_user_presses_q() {
  char c = getch();

  if (c == 'q') {
    endwin();
    exit(EXIT_SUCCESS);
  }
}


/**
 * Entry point for the program.
 */
int main(int argc, char** argv) {
  flags flgs {10, CPU};
  parse_cmd_line(argc, argv, flgs);

  // ncurses initialization
  initscr();

  // Don't show a cursor.
  curs_set(FALSE);

  // Set getch to return after 1000 milliseconds; this allows the program to
  // immediately respond to user input while not blocking indefinitely.
  timeout(flgs.delay * 100);

  SystemInfo prev = get_system_info();

  SortFn sort_fn = &compareCpu;
  switch (flgs.sort_key) {
  case PID:
    sort_fn = &comparePid;
    break;
  case MEM:
    sort_fn = &compareMem;
    break;
  case TIME:
    sort_fn = &compareTime;
    break;
  case CPU:
  default:
    sort_fn = &compareCpu;
    break;
  };

  while (true) {
    SystemInfo current = get_system_info();
    update_cpu_percent(prev, current);

    wclear(stdscr);
    // Display the counter using printw (an ncurses function)

    sort(current.processes.begin(), current.processes.end(), sort_fn);

    print_uptime(current);
    print_load_average(current.load_average);
    print_num_processes(current);
    print_processors(prev.cpus, current.cpus);
    print_memory(current.memory_info);
    print_processes(current.processes);

    // Redraw the screen.
    refresh();

    // update previous variables
    prev = current;

    // End the loop and exit if Q is pressed
    exit_if_user_presses_q();
  }

  // ncurses teardown
  endwin();

  return EXIT_SUCCESS;
}


void update_cpu_percent(SystemInfo& prev, SystemInfo& current) {
  CpuInfo delta = current.cpus[1] - prev.cpus[1];

  // calculate the cpu_percent for each of the processes
  for (ProcessInfo& curr_proc : current.processes) {
    for (ProcessInfo& prev_proc : prev.processes) {
      // find the current and previous process of the same pid
      if (curr_proc.pid == prev_proc.pid) {
        // get total execution time for this process in this time step
        unsigned long proc_time = curr_proc.utime + curr_proc.stime
                                - prev_proc.utime - prev_proc.stime;
        // set percent of cpu time
        curr_proc.cpu_percent = (double)proc_time / (double)delta.total_time() * 100.0;
        break;
      } else {
        curr_proc.cpu_percent = 0.0;
      }
    }
  }
}
