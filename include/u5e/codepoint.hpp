#ifndef INCLUDED_U5E_CODEPOINT_HPP
#define INCLUDED_U5E_CODEPOINT_HPP

#include <inttypes.h>

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
    int value;
    constexpr codepoint() : value(0) { };
    constexpr codepoint(int32_t v) : value(v) { };
    constexpr codepoint(const codepoint&) = default;
    constexpr codepoint(codepoint&&) = default;
  };
  constexpr bool operator==(const codepoint& a, const codepoint& b) { return a.value == b.value; };
  constexpr bool operator==(const int a, const codepoint& b) { return a == b.value; };
  constexpr bool operator==(const codepoint& a, const int b) { return a.value == b; };
}

#endif
