#ifndef INCLUDED_U5E_UTF8_STRING_VIEW_GRAPHEME_ITERATOR
#define INCLUDED_U5E_UTF8_STRING_VIEW_GRAPHEME_ITERATOR

#include <u5e/utf8_string_view.hpp>
#include <u5e/grapheme_iterator.hpp>

namespace u5e {
  typedef grapheme_iterator<utf8_string_view> utf8_string_view_grapheme_iterator;
};

#endif
