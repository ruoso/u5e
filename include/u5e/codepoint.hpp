#ifndef INCLUDED_U5E_CODEPOINT_HPP
#define INCLUDED_U5E_CODEPOINT_HPP

#include <inttypes.h>

namespace u5e {
  /**
   * u5e::codepoint
   *
   * Since a codepoint is an important element in the unicode
   * standard, we define a typedef specifically such that we can
   * reference codepoint by its proper name in the entire API.
   */
  typedef int32_t codepoint;
}

#endif
