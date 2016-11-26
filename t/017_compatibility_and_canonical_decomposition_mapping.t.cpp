#include "gtest/gtest.h"

#include <u5e/props/compatibility_and_canonical_decomposition_mapping.hpp>

TEST(t_009_compatibility_and_canonical_decomposition_mapping, no_d) {
  int const * decomposed =
    u5e::props::compatibility_and_canonical_decomposition_mapping::resolve(191);
  ASSERT_EQ(NULL, decomposed);
};

TEST(t_009_canonical_decomposition_mapping, multiple_chars) {
  int const * decomposed =
    u5e::props::compatibility_and_canonical_decomposition_mapping::resolve(192);
  ASSERT_EQ(65, *decomposed);
  decomposed++;
  ASSERT_EQ(768, *decomposed);
  decomposed++;
  ASSERT_EQ(0, *decomposed);
};

TEST(t_009_canonical_decomposition_mapping, single_chars) {
  int const * decomposed =
    u5e::props::compatibility_and_canonical_decomposition_mapping::resolve
    (195101);
  ASSERT_EQ(173568, *decomposed);
  decomposed++;
  ASSERT_EQ(0, *decomposed);
};
