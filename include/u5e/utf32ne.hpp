#ifndef INCLUDED_U5E_UTF32NE
#define INCLUDED_U5E_UTF32NE

#include <type_traits>
#include <u5e/encoding_assertion.hpp>
#include <u5e/codepoint.hpp>

namespace u5e {
  /**
   * \brief Architecture-specific type to interface UTF32BE or UTF32LE
   *
   * utf32ne is not an encoding. It is a type that should be used to
   * interface with either UTF32BE or with UTF32LE depending on what
   * the native endianess is.
   *
   * Because utf32 with the native endianess can be used natively,
   * there's no special logic and everything is delegated to the
   * native types.
   */
  class utf32ne {
  public:
    //@{
    /**
     * Delegate to the underlying iterator
     */
    template <typename NativeString>
    using iterator = typename NativeString::iterator;

    template <typename NativeString>
    using const_iterator = typename NativeString::const_iterator;

    template <typename NativeString>
    static typename NativeString::const_iterator
    native_const_iterator(typename NativeString::const_iterator it) {
      return it;
    }

    template <typename InputNativeIterator, typename OutputNativeString>
    static void append_from_utf32ne
    (InputNativeIterator first, InputNativeIterator last,
     OutputNativeString& output) {
      output.append(first, last);
    }

    //@}
  };
}

#endif
