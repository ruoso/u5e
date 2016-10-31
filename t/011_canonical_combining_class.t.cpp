#include "gtest/gtest.h"

#include <u5e/props/canonical_combining_class.hpp>

TEST(t_011_canonical_combining_class, def) {
  int val =
    u5e::props::canonical_combining_class::resolve(191);
  ASSERT_EQ(0, val);
};

TEST(t_011_canonical_combining_class, found1) {
  int val =
    u5e::props::canonical_combining_class::resolve(770);
  ASSERT_EQ(230, val);
};

TEST(t_011_canonical_combining_class, found2) {
  int val =
    u5e::props::canonical_combining_class::resolve(1479);
  ASSERT_EQ(18, val);
};

TEST(t_011_canonical_combining_class, found3) {
  int val =
    u5e::props::canonical_combining_class::resolve(119145);
  ASSERT_EQ(1, val);
};

TEST(t_011_canonical_combining_class, found4) {
  int val =
    u5e::props::canonical_combining_class::resolve(119149);
  ASSERT_EQ(226, val);
};

TEST(t_011_canonical_combining_class, found5) {
  int val =
    u5e::props::canonical_combining_class::resolve(119150);
  ASSERT_EQ(216, val);
};
