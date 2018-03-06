#include "flags.h"
#include <stdlib.h>


void parse_cmd_line(int argc, char ** argv, flags& flgs) {
  static struct option long_options[] = {
    {"delay",    required_argument, NULL, 'd'},
    {"sort-key", required_argument, NULL, 's'},
    {"help",     no_argument,       NULL, 'h'},
    {0, 0, 0, 0}
  };

  while (true) {
    int option_index = 0;
    int flag_char = getopt_long(argc, argv, "d:s:h", long_options, &option_index);

    if (flag_char == -1) {
      break;
    }

    switch (flag_char) {
    case 0:
      break;
    case 'd':
      flgs.delay = atoi(optarg);
      break;
    case 's':
      if ((std::string)optarg == "MEM") {
        flgs.sort_key = MEM;
      } else if ((std::string)optarg == "TIME") {
        flgs.sort_key = TIME;
      } else if ((std::string)optarg == "CPU") {
        flgs.sort_key = CPU;
      } else if ((std::string)optarg == "PID") {
        flgs.sort_key = PID;
      } else {
        printf("Incompatable sorting method.\n");
        print_help();
      }
      break;
    case 'h':
    case '?':
      print_help();
      break;
    default:
      exit(EXIT_FAILURE);
    }
  }

  return;
}

void print_help() {
  printf("Usage:\n");
  printf("  ./mytop [OPTION...]\n");
  printf("\n Options:\n");
  printf("  -h, --help            | Show this help.\n");
  printf("  -d, --delay=NUMBER    | Set the delay in tenths of a second.\n");
  printf("  -s, --sort-key COLUMN | Set the sorting column:\n");
  printf("      Columns:\n");
  printf("         PID:  sort by process id\n");
  printf("         CPU:  sort by process cpu usage\n");
  printf("         MEM:  sort by process memory usage\n");
  printf("         TIME: sort by process time\n");
  exit(EXIT_SUCCESS);
}
