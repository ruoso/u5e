#ifndef INCLUDED_U5E_UTF32NE_STRING
#define INCLUDED_U5E_UTF32NE_STRING

#include <string>
#include <u5e/basic_encodedstring.hpp>
#include <u5e/utf32ne.hpp>

namespace u5e {
  /**
   * \class u5e::utf32ne_string
   * \brief Typedef: basic_encodedstring of utf32ne and std::basic_string<int>
   *
   * Although this is a typedef, it shows up in doxygen as a class for
   * better discoverability.
   *
   * \typedef utf32ne_string
   * \brief A basic_encodedstring of utf32ne and std::basic_string<int>
   */
  typedef basic_encodedstring<utf32ne,
                              std::basic_string<int>>
    utf32ne_string;
};

#endif
