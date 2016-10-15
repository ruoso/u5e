#ifndef INCLUDED_U5E_UTF8_STRING_VIEW_GRAPHEME
#define INCLUDED_U5E_UTF8_STRING_VIEW_GRAPHEME

#include <u5e/basic_grapheme.hpp>
#include <u5e/utf8_string_view.hpp>

namespace u5e {
  /**
   * utf8_string_view_grapheme is a grapheme of a utf8_string_view
   */
  typedef basic_grapheme<utf8_string_view> utf8_string_view_grapheme;
};

#endif
