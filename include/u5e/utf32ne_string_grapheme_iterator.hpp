#ifndef INCLUDED_U5E_UTF32NE_STRING_GRAPHEME_ITERATOR
#define INCLUDED_U5E_UTF32NE_STRING_GRAPHEME_ITERATOR

#include <u5e/utf32ne_string_grapheme.hpp>
#include <u5e/basic_grapheme_iterator.hpp>

namespace u5e {
  typedef basic_grapheme_iterator<utf32ne_string>
  utf32ne_string_grapheme_iterator;
};

#endif
