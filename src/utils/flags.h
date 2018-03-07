#pragma once
#include <string>
#include <iostream>
#include <getopt.h>

enum sort_type {
  PID,
  MEM,
  TIME,
  CPU
};

struct flags {
  int delay;         // 10ths of a second
  sort_type sort_key;
};

void parse_cmd_line(int argc, char ** argv, flags& flgs);

void print_help();
