#include "gtest/gtest.h"

#include <u5e/utf32ne_string.hpp>
#include <u5e/filter.hpp>
#include <u5e/normalization_form_kc.hpp>

TEST(t_012_normalization_form_d_utf32ne, basic) { 
  u5e::utf32ne_string str({ 0x1e9b, 0x0323 });
  u5e::utf32ne_string output;
  int count =
    u5e::filter(str.grapheme_begin(), str.grapheme_end(),
                output,
                u5e::normalization_form_kc<u5e::utf32ne_string>);
  ASSERT_EQ( 0x1e69 , output.native_string[0]);
  ASSERT_EQ(1, count);
};
