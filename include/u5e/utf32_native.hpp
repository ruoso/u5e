#ifndef INCLUDED_U5E_UTF32_NATIVE
#define INCLUDED_U5E_UTF32_NATIVE

#include <type_traits>
#include <u5e/encoding_assertion.hpp>
#include <u5e/codepoint.hpp>

namespace u5e {
  /**
   * u5e::utf32_native
   *
   * The native utf32 encoding is built with the native 32 bit
   * integer type. It is specially more useful for cases where
   * you need to do extensive manipulation on text, since it
   * allows you to have constant random access time.
   */
  class utf32_native {
  public:
    template <typename UnderlyingString>
    using iterator = typename UnderlyingString::iterator;

    template <typename UnderlyingString>
    using const_iterator = typename UnderlyingString::const_iterator;
  };
}

#endif
