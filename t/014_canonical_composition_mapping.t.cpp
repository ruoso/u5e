#include "gtest/gtest.h"

#include <u5e/props/canonical_composition_mapping.hpp>

TEST(t_014_canonical_composition_mapping, no_decomposition) {
  int d;
  // codepoint 63 is not the start of a decomposition
  bool r = u5e::props::canonical_composition_mapping::resolve(63,123,&d);
  ASSERT_EQ(false, r);
};

TEST(t_014_canonical_composition_mapping, no_decomposition_2) {
  int d;
  // 65 does not have 123 as a second codepoint in a decomposition
  bool r = u5e::props::canonical_composition_mapping::resolve(65,123,&d);
  ASSERT_EQ(false, r);
};

TEST(t_014_canonical_composition_mapping, match) {
  int d;
  // 65, 770 has 194 as the composition
  bool r = u5e::props::canonical_composition_mapping::resolve(65,770,&d);
  ASSERT_EQ(true, r);
  ASSERT_EQ(194, d);
};
