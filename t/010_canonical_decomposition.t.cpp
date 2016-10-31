#include "gtest/gtest.h"

#include <u5e/utf32ne_string_view.hpp>
#include <u5e/utf32ne_string.hpp>
#include <u5e/filter.hpp>
#include <u5e/canonical_decomposition.hpp>
#include <experimental/string_view>

using std::experimental::basic_string_view;

TEST(t_010_canonical_decomposition, no_decomposition) {
  const int r[1] = { 0xC0 };
  basic_string_view<int> b(r, 1);
  u5e::utf32ne_string_view input(b);
  u5e::utf32ne_string output;
  int count =
    u5e::filter(input.codepoint_cbegin(), input.codepoint_cend(),
                output, u5e::canonical_decomposition<u5e::utf32ne_string>);
  ASSERT_EQ(2, count);
  ASSERT_EQ(0x0041, output.native_string[0]);
  ASSERT_EQ(0x0300, output.native_string[1]);
};
