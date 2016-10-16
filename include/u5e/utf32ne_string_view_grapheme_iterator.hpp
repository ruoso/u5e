#ifndef INCLUDED_U5E_UTF32NE_STRING_VIEW_GRAPHEME_ITERATOR
#define INCLUDED_U5E_UTF32NE_STRING_VIEW_GRAPHEME_ITERATOR

#include <u5e/utf32ne_string_view.hpp>
#include <u5e/basic_grapheme_iterator.hpp>

namespace u5e {
  /**
   * \class u5e::utf32ne_string_view_grapheme_iterator
   * \brief A basic_grapheme_iterator of utf32ne_string_view
   */
  typedef basic_grapheme_iterator<utf32ne_string_view>
  utf32ne_string_view_grapheme_iterator;
};

#endif
