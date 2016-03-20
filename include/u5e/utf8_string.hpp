#ifndef INCLUDED_U5E_UTF8_STRING
#define INCLUDED_U5E_UTF8_STRING

#include <u5e/basic_encodedstring.hpp>
#include <u5e/utf8.hpp>

namespace u5e {
  typedef basic_encodedstring<utf8, std::string> utf8_string;
};

#endif
