#include "gtest/gtest.h"

#include <u5e/utf32ne_string.hpp>
#include <u5e/filter.hpp>
#include <u5e/normalization_form_d.hpp>

TEST(t_012_normalization_form_d_utf32ne, basic) { 
  u5e::utf32ne_string str({ 0xC4, 0xFB03, 'n' });
  u5e::utf32ne_string output;
  int count =
    u5e::filter(str.grapheme_begin(), str.grapheme_end(),
                output,
                u5e::normalization_form_d<u5e::utf32ne_string>);
  ASSERT_EQ(4, count);
  ASSERT_EQ('A', output.native_string[0]);
  ASSERT_EQ(0x308, output.native_string[1]);
  ASSERT_EQ(0xFB03, output.native_string[2]);
  ASSERT_EQ('n', output.native_string[3]);
};
