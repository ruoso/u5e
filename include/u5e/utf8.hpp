#ifndef INCLUDED_U5E_UTF8
#define INCLUDED_U5E_UTF8

#include <iterator>
#include <cstring>
#include <type_traits>
#include <u5e/codepoint.hpp>
#include <u5e/encoding_assertion.hpp>
#include <u5e/utf8_utils.hpp>
#include <u5e/utf8_iterator.hpp>


namespace u5e {
  /**
   * u5e::utf8
   *
   * Handles utf8 encoded data
   */
    
  class utf8 {
  public:
    template <typename UnderlyingString>
    using iterator = utf8_iterator<typename UnderlyingString::iterator>;

    template <typename UnderlyingString>
    using const_iterator = utf8_const_iterator<typename UnderlyingString::const_iterator>;

  };
}

#endif
