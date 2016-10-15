#ifndef INCLUDED_U5E_UTF8_STRING_GRAPHEME_ITERATOR
#define INCLUDED_U5E_UTF8_STRING_GRAPHEME_ITERATOR

#include <u5e/utf8_string_grapheme.hpp>
#include <u5e/basic_grapheme_iterator.hpp>

namespace u5e {
  /**
   * utf8_string_grapheme_iterator is a grapheme iterator over a
   * utf8_string.
   */
  typedef basic_grapheme_iterator<utf8_string>
  utf8_string_grapheme_iterator;
};

#endif
