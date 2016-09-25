#include "gtest/gtest.h"

#include <string>
#include <sstream>

#include <u5e/codepoint.hpp>
#include <u5e/utf8_string.hpp>
#include <u5e/utf8_string_grapheme.hpp>
#include <u5e/utf8_string_grapheme_iterator.hpp>
#include <u5e/utf32ne_string.hpp>
#include <u5e/utf32ne_string_grapheme.hpp>
#include <u5e/utf32ne_string_grapheme_iterator.hpp>

using u5e::codepoint;
using u5e::utf8_string;
using u5e::utf8_string_grapheme;
using u5e::utf8_string_grapheme_iterator;
using u5e::utf32ne_string;
using u5e::utf32ne_string_grapheme;
using u5e::utf32ne_string_grapheme_iterator;

TEST(t_006_utf8_string_grapheme_iterator, utf8) {
  // this is a decomposed grapheme
  utf8_string str("Ola\xCC\x81!");

  // now we get a grapheme iterator from the utf8 iterator
  utf8_string_grapheme_iterator gi(str.cbegin(), str.cend());

  // the current grapheme
  utf8_string_grapheme g(*gi);
  // has an inner iterator
  utf8_string::const_iterator ci(g.codepoint_begin());
  // which points to a codepoint
  codepoint c(*ci);

  // first grapheme
  ASSERT_EQ('O', c);
  ci++;
  ASSERT_TRUE(ci == g.codepoint_end());

  // advance
  gi++;

  // second grapheme
  g = *gi;
  ci = g.codepoint_begin();
  c = *ci;
  ASSERT_EQ('l', c);
  ci++;
  ASSERT_TRUE(ci == g.codepoint_end());

  // advance
  gi++;

  // third grapheme
  // this one has two codepoints
  g = *gi;
  ci = g.codepoint_begin();
  c = *ci;
  ASSERT_EQ('a', c);
  ci++;
  c = *ci;
  ASSERT_EQ(769, c);
  ci++;
  ASSERT_TRUE(ci == g.codepoint_end());
  
  // advance
  gi++;

  // fourth grapheme
  g = *gi;
  ci = g.codepoint_begin();
  c = *ci;
  ASSERT_EQ('!', c);
  ci++;
  ASSERT_TRUE(ci == g.codepoint_end());

  // advance
  gi++;
  ASSERT_TRUE(gi == str.cend());

};

TEST(t_006_utf8_string_grapheme_iterator, utf32ne) {
  // this is a decomposed grapheme
  utf32ne_string str({ 'O', 'l', 'a', 769, '!' });

  // now we get a grapheme iterator from the utf32ne iterator
  utf32ne_string_grapheme_iterator gi(str.cbegin(), str.cend());

  // the current grapheme
  utf32ne_string_grapheme g(*gi);
  // has an inner iterator
  utf32ne_string::const_iterator ci(g.codepoint_begin());
  // which points to a codepoint
  codepoint c(*ci);

  // first grapheme
  ASSERT_EQ('O', c);
  ci++;
  ASSERT_TRUE(ci == g.codepoint_end());

  // advance
  gi++;

  // second grapheme
  g = *gi;
  ci = g.codepoint_begin();
  c = *ci;
  ASSERT_EQ('l', c);
  ci++;
  ASSERT_TRUE(ci == g.codepoint_end());

  // advance
  gi++;

  // third grapheme
  // this one has two codepoints
  g = *gi;
  ci = g.codepoint_begin();
  c = *ci;
  ASSERT_EQ('a', c);
  ci++;
  c = *ci;
  ASSERT_EQ(769, c);
  ci++;
  ASSERT_TRUE(ci == g.codepoint_end());
  
  // advance
  gi++;

  // fourth grapheme
  g = *gi;
  ci = g.codepoint_begin();
  c = *ci;
  ASSERT_EQ('!', c);
  ci++;
  ASSERT_TRUE(ci == g.codepoint_end());

  // advance
  gi++;
  ASSERT_TRUE(gi == str.cend());

};
