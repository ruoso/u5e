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
   * underlying types.
   */
  class utf32ne {
  public:
    //@{
    /**
     * Delegate to the underlying iterator
     */
    template <typename UnderlyingString>
    using iterator = typename UnderlyingString::iterator;

    template <typename UnderlyingString>
    using const_iterator = typename UnderlyingString::const_iterator;
    //@}
  };
}

#endif
