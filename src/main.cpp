/**
 * Contains the main() routine of what will eventually be your version of top.
 */

#include "info/cpu_info.h"
#include "info/system_info.h"
#include "utils/display.h"
#include <cstdlib>
#include <ncurses.h>

using namespace std;


void update_cpu_percent(const SystemInfo& previous, const SystemInfo& current);


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
int main() {
  // ncurses initialization
  initscr();

  // Don't show a cursor.
  curs_set(FALSE);

  // Set getch to return after 1000 milliseconds; this allows the program to
  // immediately respond to user input while not blocking indefinitely.
  timeout(1000);

  SystemInfo prev = get_system_info();

  while (true) {
    SystemInfo current = get_system_info();
    update_cpu_percent(prev, current);

    wclear(stdscr);
    // Display the counter using printw (an ncurses function)

    print_uptime(current);
    print_load_average(current);
    print_processors(current);

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


void update_cpu_percent(const SystemInfo& prev, const SystemInfo& current) {
    CpuInfo delta = current.cpus[0] - prev.cpus[0];

    // calculate the cpu_percent for each of the processes
    for (ProcessInfo curr_proc : current.processes) {
      for (ProcessInfo prev_proc : prev.processes) {
        // find the current and previous process of the same pid
        if (curr_proc.pid == prev_proc.pid) {
          // get total execution time for this process in this time step
          unsigned long proc_time = curr_proc.utime + curr_proc.stime
                                  + curr_proc.cutime + curr_proc.cstime
                                  - prev_proc.utime - prev_proc.stime
                                  - prev_proc.cutime - prev_proc.cstime;
          // set percent of cpu time
          curr_proc.cpu_percent = (double)proc_time / delta.total_time();
          break;
        }
      }
    }
}
