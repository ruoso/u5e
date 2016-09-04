#ifndef INCLUDED_U5E_CODEPOINT_HPP
#define INCLUDED_U5E_CODEPOINT_HPP

#include <u5e/codepoint_traits.hpp>

namespace u5e {
  /**
   * u5e::codepoint
   *
   * codepoint is an explicity class in order to hijack overloads,
   * such that we only build codepoints out of known encodings and we
   * only write to encodings out of known codepoints.
   */
  class codepoint {
  public:
    codepoint_traits::int_type value;
    codepoint() : value(0) { };
    codepoint(int32_t v) : value(v) { };
    codepoint(const codepoint& x) = default;
    codepoint& operator=(const codepoint& x) = default;
    operator int() const { return value; };
  };
  constexpr bool operator==(const codepoint& a, const codepoint& b) { return a.value == b.value; };
  constexpr bool operator==(const codepoint_traits::int_type a, const codepoint& b) { return a == b.value; };
  constexpr bool operator==(const codepoint& a, const codepoint_traits::int_type b) { return a.value == b; };
}

#endif
