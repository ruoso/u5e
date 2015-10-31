#include <u5e/utf32_native.hpp>
#include <u5e/codepoint.hpp>
#include "gtest/gtest.h"

#include <experimental/string_view>

using std::experimental::basic_string_view;
using std::basic_string;
using u5e::codepoint;
using u5e::utf32_native;

TEST(t_002_utf32_encoded_iterator, constructor1a) {
  const codepoint r[5] = { 'H', 'e', 'l' ,'l', 'o' };
  basic_string_view<codepoint> b(r, 5);
  utf32_native<basic_string_view<codepoint>> e(b);
}

TEST(t_002_utf32_encoded_iterator, constructor1b) {
  const codepoint r[5] = { 'H', 'e', 'l' ,'l', 'o' };
  basic_string<codepoint> b(r, 5);
  utf32_native<basic_string<codepoint>> e(b);
}

TEST(t_002_utf32_encoded_iterator, constructor2a) {
  const codepoint r[5] = { 'H', 'e', 'l' ,'l', 'o' };
  basic_string_view<codepoint> b(r, 5);
  utf32_native<basic_string_view<codepoint>> e1(b);
  utf32_native<basic_string_view<codepoint>> e2(e1);
}

TEST(t_002_utf32_encoded_iterator, constructor2b) {
  const codepoint r[5] = { 'H', 'e', 'l' ,'l', 'o' };
  basic_string<codepoint> b(r, 5);
  utf32_native<basic_string<codepoint>> e1(b);
  utf32_native<basic_string<codepoint>> e2(e1);
}

TEST(t_002_utf32_encoded_iterator, iteratora) {
  const codepoint r[5] = { 'H', 'e', 'l' ,'l', 'o' };
  basic_string_view<codepoint> b(r, 5);
  utf32_native<basic_string_view<codepoint>> e(b);
  utf32_native<basic_string_view<codepoint>>::iterator it = e.begin();
  ASSERT_EQ(*it, 'H');
  it++;
  ASSERT_EQ(*it, 'e');
  it++;
  ASSERT_EQ(*it, 'l');
  it++;
  ASSERT_EQ(*it, 'l');
  it++;
  ASSERT_EQ(*it, 'o');
  it++;
  ASSERT_EQ(it, e.end());
}

TEST(t_002_utf32_encoded_iterator, iteratorb) {
  const codepoint r[5] = { 'H', 'e', 'l' ,'l', 'o' };
  basic_string<codepoint> b(r, 5);
  utf32_native<basic_string<codepoint>> e(b);
  utf32_native<basic_string<codepoint>>::iterator it = e.begin();
  ASSERT_EQ(*it, 'H');
  it++;
  ASSERT_EQ(*it, 'e');
  it++;
  ASSERT_EQ(*it, 'l');
  it++;
  ASSERT_EQ(*it, 'l');
  it++;
  ASSERT_EQ(*it, 'o');
  it++;
  ASSERT_EQ(it, e.end());
}
