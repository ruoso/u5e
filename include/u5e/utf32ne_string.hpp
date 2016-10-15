#ifndef INCLUDED_U5E_UTF32NE_STRING
#define INCLUDED_U5E_UTF32NE_STRING

#include <string>
#include <u5e/basic_encodedstring.hpp>
#include <u5e/utf32ne.hpp>

namespace u5e {
  /**
   * utf32ne_string is an encoded string over std::basic_string<int>
   */
  typedef basic_encodedstring<utf32ne,
                              std::basic_string<int>>
    utf32ne_string;
};

#endif
