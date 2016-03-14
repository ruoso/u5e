#include <u5e/version.hpp>
#include "gtest/gtest.h"

TEST(t_001_version, currentversion) {
  EXPECT_EQ(0, u5e::version::major);
  EXPECT_EQ(0, u5e::version::minor);
  EXPECT_EQ(0, u5e::version::patch);
  EXPECT_EQ(0, u5e::version::lib_major);
  EXPECT_EQ(0, u5e::version::lib_minor);
  EXPECT_EQ(0, u5e::version::lib_patch);
}
