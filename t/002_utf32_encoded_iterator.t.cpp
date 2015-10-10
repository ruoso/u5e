#include <u5e/enc/utf32_native.hpp>
#include <u5e/codepoint.hpp>
#include <u5e/encoded_buffer.hpp>
#include "gtest/gtest.h"

using u5e::encoded_buffer;
using u5e::codepoint;
using u5e::enc::utf32_native;

TEST(t_002_utf32_encoded_iterator, constructor1) {
  const codepoint r[5] = { 'H', 'e', 'l' ,'l', 'o' };
  u5e::buffer<codepoint> b(r, 5);
  encoded_buffer<utf32_native> e(b);
}

TEST(t_002_utf32_encoded_iterator, constructor2) {
  const codepoint r[5] = { 'H', 'e', 'l' ,'l', 'o' };
  encoded_buffer<utf32_native> e(r, 5);
}

TEST(t_002_utf32_encoded_iterator, constructor3) {
  const codepoint r[5] = { 'H', 'e', 'l' ,'l', 'o' };
  encoded_buffer<utf32_native> e1(r, 5);
  encoded_buffer<utf32_native> e2(e1);
}

TEST(t_002_utf32_encoded_iterator, iterator) {
  const codepoint r[5] = { 'H', 'e', 'l' ,'l', 'o' };
  encoded_buffer<utf32_native> e(r, 5);
  utf32_native::iterator it = e.begin();
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
