#ifndef INCLUDED_U5E_UTF8
#define INCLUDED_U5E_UTF8

#include <iterator>
#include <cstring>
#include <type_traits>
#include <u5e/codepoint.hpp>
#include <u5e/encoding_assertion.hpp>
#include <u5e/utf8_iterator.hpp>


namespace u5e {
  /**
   * \brief Encoding type for UTF8 text.
   * Unlike UTF16 and UTF32, UTF8 is endian independent.
   */
  class utf8 {
  public:

    /**
     * Delegated to utf8_iterator of the underlying type.
     * \tparam UnderlyingString the underlying string type with utf8 data
     */
    template <typename UnderlyingString>
    using iterator =
      utf8_iterator<typename UnderlyingString::iterator>;

    /**
     * Delegated to utf8_const_iterator of the underlying type
     * \tparam UnderlingString the underlying string type with utf8 data
     */
    template <typename UnderlyingString>
    using const_iterator =
      utf8_const_iterator<typename UnderlyingString::const_iterator>;

  };
}

#endif
