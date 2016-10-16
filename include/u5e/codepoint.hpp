#ifndef INCLUDED_U5E_CODEPOINT_HPP
#define INCLUDED_U5E_CODEPOINT_HPP

#include <u5e/codepoint_traits.hpp>

namespace u5e {
  /**
   * \brief Native representation of a codepoint
   *
   * Explicity class in order to hijack overloads, such that we only
   * build codepoints out of known encodings and we only write to
   * encodings out of known codepoints.
   */
  class codepoint {
  public:
    /**
     * A codepoint has an integer value type.
     */
    codepoint_traits::int_type value;

    /**
     * Default constructor, starts as NULL.
     */
    constexpr codepoint() : value(0) { };

    /**
     * Implicit constructor from an integer value.
     */
    constexpr codepoint(int32_t v) : value(v) { };

    /**
     * Copy constructor.
     */
    constexpr codepoint(const codepoint& x) = default;

    /**
     * Assignment operator from another codepoint.
     */
    constexpr codepoint& operator=(const codepoint& x) = default;

    /**
     * Assignment operator from an int.
     */
    constexpr codepoint& operator=(int c) { value = c; return *this; };

    /**
     * Override int operator to return the codepoint value.
     */
    constexpr operator int() const { return value; };
  };

  /**
   * Compare two codepoints by comparing their values.
   */
  constexpr bool operator==(const codepoint& a, const codepoint& b) { return a.value == b.value; };

  //@{
  /**
   * Compare an int to a codepoint by comparing the codepoint's value
   * with the integer.
   */
  constexpr bool operator==(const codepoint_traits::int_type a, const codepoint& b) { return a == b.value; };
  constexpr bool operator==(const codepoint& a, const codepoint_traits::int_type b) { return a.value == b; };
  //@}
}

#endif
