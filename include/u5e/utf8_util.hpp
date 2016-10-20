#ifndef INCLUDED_U5E_UTF8_UTIL
#define INCLUDED_U5E_UTF8_UTIL

#include <cmath>
#include <algorithm>

namespace u5e {
  /**
   * \brief Basic operations necessary for implementing utf8
   */
  class utf8_util {
  public:

    /**
     * Check whether or not this is a 7bit character
     */
    inline static bool is_7bit_character(const char octet) {
      if (octet & 0b10000000) {
        return false;
      } else {
        return true;
      }
    }
    
    /**
     * Check whether or not this is octet is a codepoint continuation
     */
    inline static bool is_codepoint_continuation(const char octet) {
      if ((octet & 0b11000000) == 0b10000000) {
        return true;
      } else {
        return false;
      }
    }

    /**
     * Check whether or not this is a first octet in a sequence
     */
    inline static bool is_codepoint_start(const char octet) {
      if ((octet & 0b11000000) == 0b11000000) {
        return true;
      } else {
        return false;
      }
    }
    
    /**
     * Find the codepoint size given the first utf8 octet
     */
    inline static int codepoint_size(const char first_octet) {
      // count leading zeros on bitwise negated first octet.  for
      // single-octet codepoints, this would return 0, so we do
      // std::max for 1 for those cases.
      return std::max(__builtin_clz(~(first_octet << 24)),1);
    }

    /**
     * How many octets will this codepoint take
     */
    inline static int encoded_size(int value) {
      return std::ceil((float)(32 - __builtin_clz(value) - 1) / (float)6);
    }
    
  };
}

#endif
