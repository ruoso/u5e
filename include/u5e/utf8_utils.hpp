#ifndef INCLUDED_U5E_UTF8_UTILS
#define INCLUDED_U5E_UTF8_UTILS

#include <cmath>

namespace u5e {
  class utf8_utils {
  public:
    const static int MAX_CODEPOINT_SIZE = 6;
    static inline int codepoint_size(const char first_octet) {
      // count leading zeros on bitwise negated first octet.  for
      // single-octet codepoints, this would return 0, so we do
      // std::max for 1 for those cases.
      return std::max(__builtin_clz(~(first_octet << 24)),1);
    }
  };
}

#endif
