#include "conversions.h"
#include "gtest/gtest.h"

// test seconds convert to days, hrs, mins, secs
TEST(HumanReadable, TimeWithDay) {
  EXPECT_EQ("1 days, 15:34:19", human_readable_time(142459L));
}

// test seconds convert to days, hrs, mins, secs
TEST(HumanReadable, TimeWithoutDay) {
  EXPECT_EQ("03:58:45", human_readable_time(14325L));
}

// test seconds convert to days, hrs, mins, secs
TEST(HumanReadable, TimeLeadingZeros) {
  EXPECT_EQ("03:07:05", human_readable_time(11225L));
}

// test kB goes to MB or GB
TEST(HumanReadable, Memory) {
  EXPECT_EQ("13.5MB", human_readable_memory(13500L));
  EXPECT_EQ("135KB", human_readable_memory(135L));
}
