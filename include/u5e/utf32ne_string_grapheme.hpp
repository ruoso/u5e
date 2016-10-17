#ifndef INCLUDED_U5E_UTF32NE_STRING_GRAPHEME
#define INCLUDED_U5E_UTF32NE_STRING_GRAPHEME

#include <u5e/basic_grapheme.hpp>
#include <u5e/utf32ne_string.hpp>

namespace u5e {
  /**
   * \class u5e::utf32ne_string_grapheme
   * \brief Typedef: basic_grapheme of utf32ne_string
   *
   * Although this is a typedef, it shows up in doxygen as a class for
   * better discoverability.
   *
   * \typedef u5e::utf32ne_string_grapheme
   * \brief A basic_grapheme of utf32ne_string
   */
  typedef basic_grapheme<utf32ne_string> utf32ne_string_grapheme;
};

#endif
