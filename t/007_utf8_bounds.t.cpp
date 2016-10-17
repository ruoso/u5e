#include "gtest/gtest.h"

#include <string>
#include <u5e/utf8_bounds.hpp>

using std::string;
using u5e::utf8_bounds;

TEST(t_007_utf8_bounds, check_valid_bounds) {
  const string test_data("Ol\xC3\x81!");
  bool ret = utf8_bounds<string::const_iterator>::check
    (test_data.cbegin(), test_data.cend()); 
  ASSERT_EQ(ret, true);
};

TEST(t_007_utf8_bounds, check_invalid_bounds_start) {
  const string test_data("\x81Ol\xC3\x81!");
  bool ret = utf8_bounds<string::const_iterator>::check
    (test_data.cbegin(), test_data.cend()); 
  ASSERT_EQ(ret, false);
};

TEST(t_007_utf8_bounds, check_invalid_bounds_end) {
  const string test_data("Ol\xC3\x81!\xC3");
  bool ret = utf8_bounds<string::const_iterator>::check
    (test_data.cbegin(), test_data.cend()); 
  ASSERT_EQ(ret, false);
};

TEST(t_007_utf8_bounds, check_invalid_bounds_both) {
  const string test_data("\x81\x81Ol\xC3\x81!\xC3");
  bool ret = utf8_bounds<string::const_iterator>::check
    (test_data.cbegin(), test_data.cend()); 
  ASSERT_EQ(ret, false);
};

TEST(t_007_utf8_bounds, enforce_valid_bounds) {
  string test_data("Ol\xC3\x81!");
  string expected("Ol\xC3\x81!");
  bool ret = utf8_bounds<string::iterator>::enforce
    (test_data.begin(), test_data.end()); 
  ASSERT_EQ(ret, true);
  ASSERT_EQ(test_data, expected);
};

TEST(t_007_utf8_bounds, enforce_invalid_bounds_start) {
  string test_data("\x81\x81Ol\xC3\x81!");
  string expected("??Ol\xC3\x81!");
  bool ret = utf8_bounds<string::iterator>::enforce
    (test_data.begin(), test_data.end()); 
  ASSERT_EQ(ret, false);
  ASSERT_EQ(test_data, expected);
};

TEST(t_007_utf8_bounds, enforce_invalid_bounds_end) {
  string test_data("Ol\xC3\x81!\xC3");
  string expected("Ol\xC3\x81!?");
  bool ret = utf8_bounds<string::iterator>::enforce
    (test_data.begin(), test_data.end()); 
  ASSERT_EQ(ret, false);
  ASSERT_EQ(test_data, expected);
};

TEST(t_007_utf8_bounds, enforce_invalid_bounds_both) {
  string test_data("\x81\x81Ol\xC3\x81!\xC3");
  string expected("??Ol\xC3\x81!?");
  bool ret = utf8_bounds<string::iterator>::enforce
    (test_data.begin(), test_data.end()); 
  ASSERT_EQ(ret, false);
  ASSERT_EQ(test_data, expected);
};
