#include "../info/process_info.h"

typedef bool (*SortFn) (const ProcessInfo&, const ProcessInfo&);

bool comparePid(const ProcessInfo& lhs, const ProcessInfo& rhs);

bool compareCpu(const ProcessInfo& lhs, const ProcessInfo& rhs);

bool compareMem(const ProcessInfo& lhs, const ProcessInfo& rhs);

bool compareTime(const ProcessInfo& lhs, const ProcessInfo& rhs);
