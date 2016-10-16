#ifndef INCLUDED_U5E_UTF32NE_STRING_VIEW_GRAPHEME
#define INCLUDED_U5E_UTF32NE_STRING_VIEW_GRAPHEME

#include <u5e/basic_grapheme.hpp>
#include <u5e/utf32ne_string_view.hpp>

namespace u5e {
  /**
   * \class u5e::utf32ne_string_view_grapheme
   * \brief A basic_grapheme of utf32ne_string_view
   */
  typedef basic_grapheme<utf32ne_string_view> utf32ne_string_view_grapheme;
};

#endif
