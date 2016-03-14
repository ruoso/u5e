#include <u5e/utf32_native.hpp>
#include "gtest/gtest.h"

#include <experimental/string_view>

using std::experimental::basic_string_view;
using std::basic_string;
using u5e::utf32_native;

TEST(t_002_utf32_encoded_iterator, constructor1a) {
  const int r[5] = { 'H', 'e', 'l' ,'l', 'o' };
  basic_string_view<int> b(r, 5);
  utf32_native<basic_string_view<int>> e(b);
}

TEST(t_002_utf32_encoded_iterator, constructor1b) {
  const int r[5] = { 'H', 'e', 'l' ,'l', 'o' };
  basic_string<int> b(r, 5);
  utf32_native<basic_string<int>> e(b);
}

TEST(t_002_utf32_encoded_iterator, constructor2a) {
  const int r[5] = { 'H', 'e', 'l' ,'l', 'o' };
  basic_string_view<int> b(r, 5);
  utf32_native<basic_string_view<int>> e1(b);
  utf32_native<basic_string_view<int>> e2(e1);
}

TEST(t_002_utf32_encoded_iterator, constructor2b) {
  const int r[5] = { 'H', 'e', 'l' ,'l', 'o' };
  basic_string<int> b(r, 5);
  utf32_native<basic_string<int>> e1(b);
  utf32_native<basic_string<int>> e2(e1);
}

TEST(t_002_utf32_encoded_iterator, iteratora) {
  const int r[5] = { 'H', 'e', 'l' ,'l', 'o' };
  basic_string_view<int> b(r, 5);
  utf32_native<basic_string_view<int>> e(b);
  utf32_native<basic_string_view<int>>::iterator it = e.begin();
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
  const int r[5] = { 'H', 'e', 'l' ,'l', 'o' };
  basic_string<int> b(r, 5);
  utf32_native<basic_string<int>> e(b);
  utf32_native<basic_string<int>>::iterator it = e.begin();
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
