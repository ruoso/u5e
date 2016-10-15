#ifndef INCLUDED_U5E_UTF8_STRING_GRAPHEME
#define INCLUDED_U5E_UTF8_STRING_GRAPHEME

#include <u5e/basic_grapheme.hpp>
#include <u5e/utf8_string.hpp>

namespace u5e {
  /**
   * utf8_string_grapheme is a grapheme over a utf8_string
   */
  typedef basic_grapheme<utf8_string> utf8_string_grapheme;
};

#endif
