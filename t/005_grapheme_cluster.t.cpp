#include "gtest/gtest.h"

#include <string>
#include <sstream>

#include <u5e/codepoint.hpp>
#include <u5e/utf8_string.hpp>
#include <u5e/utf8_string_view.hpp>
#include <u5e/utf8_string_grapheme.hpp>
#include <u5e/utf8_string_view_grapheme.hpp>

using u5e::codepoint;
using u5e::utf8_string;
using u5e::utf8_string_view;
using u5e::utf8_string_grapheme;
using u5e::utf8_string_view_grapheme;

TEST(t_005_utf8_string_grapheme, constructor_1) {
  // this is a decomposed grapheme
  utf8_string str("Ola\xCC\x81!");
  utf8_string::const_iterator i = str.codepoint_cbegin();
  // "O", "l",
  i++; i++;
  utf8_string::const_iterator g_start = i;
  // "a", "\xCC\x81"
  i++; i++;
  utf8_string::const_iterator g_end = i;
  utf8_string_grapheme cluster(g_start, g_end);

  utf8_string_grapheme::const_codepoint_iterator gi
    = cluster.codepoint_begin();
  ASSERT_EQ(gi, g_start);
  codepoint c = *gi;  
  ASSERT_EQ('a', c);
  gi++;
  c = *gi;
  ASSERT_EQ(769, c);
  gi++;
  ASSERT_TRUE(gi == cluster.codepoint_end());
  ASSERT_TRUE(gi == g_end);
}

TEST(t_005_utf8_string_view_grapheme, constructor_2) {
  // this is a decomposed grapheme
  utf8_string_view str("Ola\xCC\x81!");
  utf8_string_view::const_iterator i = str.codepoint_cbegin();
  // "O", "l",
  i++; i++;
  utf8_string_view::const_iterator g_start = i;
  // "a", "\xCC\x81"
  i++; i++;
  utf8_string_view::const_iterator g_end = i;
  utf8_string_view_grapheme cluster(g_start, g_end);

  utf8_string_view_grapheme::const_codepoint_iterator gi
    = cluster.codepoint_begin();
  ASSERT_EQ(gi, g_start);
  codepoint c = *gi;  
  ASSERT_EQ('a', c);
  gi++;
  c = *gi;
  ASSERT_EQ(769, c);
  gi++;
  ASSERT_TRUE(gi == cluster.codepoint_end());
  ASSERT_TRUE(gi == g_end);
}
