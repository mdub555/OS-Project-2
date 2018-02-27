/**
 * Contains the main() routine of what will eventually be your version of top.
 */

#include "info/cpu_info.h"
#include "info/system_info.h"
#include <cstdlib>
#include <ncurses.h>

using namespace std;


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


/** Makes a progress bar starting at the current cursor position and ending
 *  at the end of the line.
 *  @arg fraction the fraction of the progress desired to display
 */
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

  int tick = 1;

  SystemInfo prev = get_system_info();

  while (true) {
    SystemInfo current = get_system_info();
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

    wclear(stdscr);
    // Display the counter using printw (an ncurses function)
    printw("Behold, the number: %d", tick++);
    for (int i = 0; i <= 10; i++) {
      progressBar(i/10.);
    }
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
