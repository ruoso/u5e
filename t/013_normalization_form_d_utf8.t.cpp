#include "gtest/gtest.h"

#include <u5e/utf8_string.hpp>
#include <u5e/filter.hpp>
#include <u5e/normalization_form_d.hpp>

TEST(t_013_normalization_form_d_utf8, basic) { 
  u5e::utf8_string str("\xC3\x84!");
  u5e::utf8_string output;
  int count =
    u5e::filter(str.grapheme_begin(), str.grapheme_end(),
                output,
                u5e::normalization_form_d<u5e::utf8_string>);
  ASSERT_EQ(3, count);
  ASSERT_STREQ("A\xCC\x88!", output.native_string.c_str());
};
