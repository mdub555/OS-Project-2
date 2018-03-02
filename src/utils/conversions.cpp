#include "conversions.h"
#include <string>
#include <sys/stat.h>
#include <math.h>

std::string human_readable_time(long seconds) {
  int sec = seconds % 60;
  seconds /= 60; // num minutes
  int min = seconds % 60;
  seconds /= 60; // num hours
  int hours = seconds % 24;
  seconds /= 24; // num days
  int days = seconds % 24;

  std::string result = "";
  if (days > 0) {
    result += std::to_string(days) + " days, ";
  }
  if (hours < 10) result += "0";
  result += std::to_string(hours) + ":";
  if (min < 10) result += "0";
  result += std::to_string(min) + ":";
  if (sec < 10) result += "0";
  result += std::to_string(sec);
  return result;
}

double round_off(double n) {
  double d = n * 100.0;
  int i = d + 0.5;
  d = (float)i / 100.0;
  return d;
}

std::string human_readable_memory(long size) {
  static const char* SIZES[] = { "KB", "MB", "GB" };
  unsigned int div = 0;
  size_t rem = 0;

  while (size >= 1000 && div < (sizeof SIZES / sizeof *SIZES)) {
    rem = (size % 1000);
    div++;
    size /= 1000;
  }

  double size_d = (float)size + (float)rem / 1000.0;
  std::string result = std::to_string(round_off(size_d));
  result.erase(result.find_last_not_of('0') + 1, std::string::npos);
  if (result[result.size()-1] == '.') result.erase(result.size()-1);
  result += (std::string)SIZES[div];
  return result;
}
