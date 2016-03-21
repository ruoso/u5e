#ifndef INCLUDED_U5E_UTF8_STRING_VIEW
#define INCLUDED_U5E_UTF8_STRING_VIEW

#include <experimental/string_view>
#include <u5e/basic_encodedstring_view.hpp>
#include <u5e/utf8_iterator.hpp>
#include <u5e/utf8.hpp>

namespace u5e {
  typedef basic_encodedstring_view<utf8, std::experimental::string_view> utf8_string_view;
};

#endif
