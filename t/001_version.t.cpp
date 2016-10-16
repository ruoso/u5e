#include <u5e/version.hpp>
#include "gtest/gtest.h"

TEST(t_001_version, currentversion) {
  EXPECT_EQ(0, u5e::version::compile_time::major);
  EXPECT_EQ(0, u5e::version::compile_time::minor);
  EXPECT_EQ(0, u5e::version::compile_time::patch);
  EXPECT_EQ(0, u5e::version::run_time::major);
  EXPECT_EQ(0, u5e::version::run_time::minor);
  EXPECT_EQ(0, u5e::version::run_time::patch);
}
