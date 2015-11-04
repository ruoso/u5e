#include <u5e/utf8.hpp>
#include <u5e/codepoint.hpp>
#include "gtest/gtest.h"
#include <experimental/string_view>

using u5e::codepoint;
using u5e::utf8;
usnig u5e::utf8_iterator;
using std::experimental::string_view;
using std::string;

TEST(t_003_utf8_encoded_iterator, constructor1a) {
  string_view str("Ol\xC3\x81!");
  utf8<string_view> e(str);
}

TEST(t_003_utf8_encoded_iterator, constructor1b) {
  string str("Ol\xC3\x81!");
  utf8<string> e(str);
}

TEST(t_003_utf8_encoded_iterator, constructor2a) {
  string_view str("Ol\xC3\x81!");
  utf8<string_view> e1(str);
  utf8<string_view> e2(e1);
}

TEST(t_003_utf8_encoded_iterator, constructor2b) {
  string str("Ol\xC3\x81!");
  utf8<string> e1(str);
  utf8<string> e2(e1);
}

TEST(t_003_utf8_encoded_iterator, iteratora) {
  string_view str("Ol\xC3\x81!");
  utf8<string_view> e(str);
  utf8<string_view>::iterator it = e.begin();
  ASSERT_EQ(*it, 'O');
  it++;
  ASSERT_EQ(*it, 'l');
  it++;
  ASSERT_EQ(*it, 0xC1);
  it++;
  ASSERT_EQ(*it, '!');
  it++;
  ASSERT_EQ(it, e.end());
}


TEST(t_003_utf8_encoded_iterator, iteratorb) {
  string str("Ol\xC3\x81!");
  utf8<string> e(str);
  utf8<string>::iterator it = e.begin();
  ASSERT_EQ(*it, 'O');
  it++;
  ASSERT_EQ(*it, 'l');
  it++;
  ASSERT_EQ(*it, 0xC1);
  it++;
  ASSERT_EQ(*it, '!');
  it++;
  ASSERT_EQ(it, e.end());
}

TEST(t_003_utf8_encoded_iterator, iteratorc) {
  const char* foo = "Ol\xC3\x81!";
  utf8_iterator<const char*> it(e.begin());
  ASSERT_EQ(*it, 'O');
  it++;
  ASSERT_EQ(*it, 'l');
  it++;
  ASSERT_EQ(*it, 0xC1);
  it++;
  ASSERT_EQ(*it, '!');
  it++;
  ASSERT_EQ(it, e.end());
}
