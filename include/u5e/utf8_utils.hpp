#ifndef INCLUDED_U5E_UTF8_UTILS
#define INCLUDED_U5E_UTF8_UTILS

namespace u5e {
  /**
   * u5e::utf8_utils
   *
   * Basic utility functions for manipulating utf8 data 
   */
  class utf8_utils {
  public:
    static const size_t max_codepoint_size = 6;
    // returns the size of the codepoint
    static inline int codepoint_size(const char first_octet) {
      int size = 1;
      if ((first_octet & 0b11000000) == 0b11000000) {
        size++;
        if ((first_octet & 0b11100000) == 0b11100000) {
          size++;
          if ((first_octet & 0b11110000) == 0b11110000) {
            size++;
            if ((first_octet & 0b11111000) == 0b11111000) {
              size++;
              if ((first_octet & 0b11111100) == 0b11111100) {
                size++;
              }
            }
          }
        }
      }
      return size;
    }

    // convert a char array into a single octet, takes the size
    // instead of looking it up again, because traversing the memory
    // already required knowing the size in the first place
    static inline codepoint
    octets_to_codepoint(char octets[max_codepoint_size], int size) {
      constexpr char mask_first_octet[6] =
        { 0b00011111, 0b00001111, 0b00000111, 0b00000011, 0b00000001 };
      constexpr char mask_other_octets = 0b00111111;
      if (size == 1) {
        return octets[0];
      } else {
        int shift_first_octet = ((size - 1) * 6);
        codepoint value =
          (octets[0] & mask_first_octet[size - 2]) << shift_first_octet;
        for (int i = 1; i < size; i++) {
          int shift = ((size - 1) - i) * 6;
          value = value | ((octets[i] & mask_other_octets) << shift);
        }
        return value;
      }
    }
  };
};

#endif
