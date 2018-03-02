#include "compare.h"

bool comparePid(const ProcessInfo& lhs, const ProcessInfo& rhs) {
  return lhs.pid < rhs.pid;
}

bool compareCpu(const ProcessInfo& lhs, const ProcessInfo& rhs) {
  return lhs.cpu_percent < rhs.cpu_percent;
}

bool compareMem(const ProcessInfo& lhs, const ProcessInfo& rhs) {
  return lhs.rss < rhs.rss;
}

bool compareTime(const ProcessInfo& lhs, const ProcessInfo& rhs) {
  return lhs.utime + lhs.stime < rhs.utime + rhs.stime;
}
