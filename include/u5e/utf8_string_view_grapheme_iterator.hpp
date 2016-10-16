#ifndef INCLUDED_U5E_UTF8_STRING_VIEW_GRAPHEME_ITERATOR
#define INCLUDED_U5E_UTF8_STRING_VIEW_GRAPHEME_ITERATOR

#include <u5e/utf8_string_view.hpp>
#include <u5e/basic_grapheme_iterator.hpp>

namespace u5e {
  /**
   * \class u5e::utf8_string_view_grapheme_iterator
   * \brief A basic_grapheme_iterator of utf8_string_view.
   */
  typedef basic_grapheme_iterator<utf8_string_view>
  utf8_string_view_grapheme_iterator;
};

#endif
