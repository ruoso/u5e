#include "gtest/gtest.h"

#include <string>
#include <sstream>

#include <u5e/basic_encodedstreambuf.hpp>
#include <u5e/utf8.hpp>
#include <u5e/utf8_stringbuf.hpp>

using std::stringbuf;
using std::string;
using u5e::basic_encodedstreambuf;
using u5e::utf8;
using u5e::codepoint;
using u5e::utf8_stringbuf;

TEST(t_004_encoded_stream, constructor_1) {
  string str("Ol\xC3\x81!");
  stringbuf ss(str);
  basic_encodedstreambuf<utf8, stringbuf> foo(ss);
}

TEST(t_004_encoded_stream, getc_1) {
  string str("Ol\xC3\x81!");
  stringbuf ss(str);
  basic_encodedstreambuf<utf8, stringbuf> ess(ss);
  codepoint c = ess.sgetc();
  ASSERT_EQ('O', c);
  c = ess.snextc();
  ASSERT_EQ('l', c);
  c = ess.snextc();
  ASSERT_EQ(0xC1, c);
  c = ess.snextc();
  ASSERT_EQ('!', c);
}

TEST(t_004_encoded_stream, getc_2) {
  string str("Ol\xC3\x81!");
  stringbuf ss(str);
  utf8_stringbuf ess(ss);
  codepoint c = ess.sgetc();
  ASSERT_EQ('O', c);
  c = ess.snextc();
  ASSERT_EQ('l', c);
  c = ess.snextc();
  ASSERT_EQ(0xC1, c);
  c = ess.snextc();
  ASSERT_EQ('!', c);
}
