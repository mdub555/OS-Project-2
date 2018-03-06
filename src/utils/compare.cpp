#include "compare.h"

// These sorting functions sort the given processes by the corresponding metric

// sort ascending
bool comparePid(const ProcessInfo& lhs, const ProcessInfo& rhs) {
  return lhs.pid < rhs.pid;
}

// sort descending
bool compareCpu(const ProcessInfo& lhs, const ProcessInfo& rhs) {
  return lhs.cpu_percent > rhs.cpu_percent;
}

// sort descending
bool compareMem(const ProcessInfo& lhs, const ProcessInfo& rhs) {
  return lhs.rss > rhs.rss;
}

// sort descending
bool compareTime(const ProcessInfo& lhs, const ProcessInfo& rhs) {
  return lhs.utime + lhs.stime > rhs.utime + rhs.stime;
}
