#include "gtest/gtest.h"

#include <u5e/utf32ne_string.hpp>
#include <u5e/filter.hpp>
#include <u5e/normalization_form_c.hpp>

TEST(t_013_normalization_form_c_utf8, basic) { 
  u5e::utf32ne_string str({ 'A', 0x308, 0xFB03, 'n' });
  u5e::utf32ne_string output;
  int count =
    u5e::filter(str.grapheme_begin(), str.grapheme_end(),
                output,
                u5e::normalization_form_c<u5e::utf32ne_string>);
  ASSERT_EQ(0xC4, output.native_string[0]);
  ASSERT_EQ(0xFB03, output.native_string[1]);
  ASSERT_EQ('n', output.native_string[2]);
  ASSERT_EQ(3, count);
};
