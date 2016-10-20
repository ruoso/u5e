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
     * Delegated to utf8_iterator of the native type.
     * \tparam NativeString the native string type with utf8 data
     */
    template <typename NativeString>
    using iterator =
      utf8_iterator<typename NativeString::iterator>;

    /**
     * Delegated to utf8_const_iterator of the native type
     * \tparam NativeString the native string type with utf8 data
     */
    template <typename NativeString>
    using const_iterator =
      utf8_const_iterator<typename NativeString::const_iterator>;

    /**
     * Get access to the native const_iterator with the native data.
     */
    template <typename NativeString>
    static typename NativeString::const_iterator
    native_const_iterator
    (utf8_const_iterator<typename NativeString::const_iterator> it) {
      it.rewind_to_start_of_codepoint(*(it.raw_iterator_));
      return it.raw_iterator_;
    }
  };
}

#endif
