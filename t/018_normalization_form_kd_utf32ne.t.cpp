#include "gtest/gtest.h"

#include <u5e/utf32ne_string.hpp>
#include <u5e/filter.hpp>
#include <u5e/normalization_form_kd.hpp>

TEST(t_012_normalization_form_kd_utf32ne, basic) { 
  u5e::utf32ne_string str({ 0xfb01 });
  u5e::utf32ne_string output;
  int count =
    u5e::filter(str.grapheme_begin(), str.grapheme_end(),
                output,
                u5e::normalization_form_kd<u5e::utf32ne_string>);
  ASSERT_EQ(2, count);
  ASSERT_EQ('f', output.native_string[0]);
  ASSERT_EQ('i', output.native_string[1]);
};

TEST(t_012_normalization_form_kd_utf32ne, basic1) { 
  u5e::utf32ne_string str({ 0x1e9b, 0x0323 });
  u5e::utf32ne_string output;
  int count =
    u5e::filter(str.grapheme_begin(), str.grapheme_end(),
                output,
                u5e::normalization_form_kd<u5e::utf32ne_string>);
  ASSERT_EQ( 's' , output.native_string[0]);
  ASSERT_EQ( 0x0323 , output.native_string[0]);
  ASSERT_EQ( 0x0307 , output.native_string[0]);
  ASSERT_EQ(3, count);
};
