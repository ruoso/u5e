#ifndef INCLUDED_U5E_UTF8_STRING_VIEW
#define INCLUDED_U5E_UTF8_STRING_VIEW

#include <experimental/string_view>
#include <u5e/basic_encodedstring.hpp>
#include <u5e/utf8_iterator.hpp>
#include <u5e/utf8.hpp>

namespace u5e {
  /**
   * \class u5e::utf8_string_view
   * \brief Typedef: basic_encodedstring of utf8 and string_view.
   *
   * Although this is a typedef, it shows up in doxygen as a class for
   * better discoverability.
   *
   * \typedef u5e::utf8_string_view
   * \brief A basic_encodedstring of utf8 and string_view.
   */
  typedef basic_encodedstring<utf8, std::experimental::string_view>
  utf8_string_view;
};

#endif
