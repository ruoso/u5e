#include <u5e/enc/utf8.hpp>
#include <u5e/codepoint.hpp>
#include <u5e/encoded_buffer.hpp>
#include "gtest/gtest.h"

using u5e::encoded_buffer;
using u5e::codepoint;
using u5e::enc::utf8;

TEST(t_003_utf8_encoded_iterator, constructor1) {
  const char r[5] = { 'O', 'l', (char)0xC3, (char)0x81, '!' };
  u5e::buffer<const char> b(r, 5);
  encoded_buffer<utf8> e(b);
}

TEST(t_003_utf8_encoded_iterator, constructor2) {
  const char r[5] = { 'O', 'l', (char)0xC3, (char)0x81, '!' };
  encoded_buffer<utf8> e(r, 5);
}

TEST(t_003_utf8_encoded_iterator, constructor3) {
  const char r[5] = { 'O', 'l', (char)0xC3, (char)0x81, '!' };
  encoded_buffer<utf8> e1(r, 5);
  encoded_buffer<utf8> e2(e1);
}

TEST(t_003_utf8_encoded_iterator, iterator) {
  const char r[5] = { 'O', 'l', (char)0xC3, (char)0x81, '!' };
  encoded_buffer<utf8> e(r, 5);
  utf8::iterator it = e.begin();
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
