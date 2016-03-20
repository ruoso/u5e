#ifndef INCLUDED_U5E_UTF32_NATIVE_STRING
#define INCLUDED_U5E_UTF32_NATIVE_STRING

#include <string>
#include <u5e/basic_encodedstring.hpp>
#include <u5e/utf32_native.hpp>

namespace u5e {
  typedef basic_encodedstring<utf32_native,
                              std::basic_string<int>>
    utf32_native_string;
};

#endif
