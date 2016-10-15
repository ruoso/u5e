#ifndef INCLUDED_U5E_UTF8_STRING_VIEW
#define INCLUDED_U5E_UTF8_STRING_VIEW

#include <experimental/string_view>
#include <u5e/basic_encodedstring.hpp>
#include <u5e/utf8_iterator.hpp>
#include <u5e/utf8.hpp>

namespace u5e {
  /**
   * utf8_string_view is a encoded string over a string_view.
   */
  typedef basic_encodedstring<utf8, std::experimental::string_view> utf8_string_view;
};

#endif
