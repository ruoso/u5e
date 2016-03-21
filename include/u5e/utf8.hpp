#ifndef INCLUDED_U5E_UTF8
#define INCLUDED_U5E_UTF8

#include <iterator>
#include <cstring>
#include <type_traits>
#include <u5e/codepoint.hpp>
#include <u5e/encoding_assertion.hpp>
#include <u5e/utf8_utils.hpp>
#include <u5e/utf8_iterator.hpp>


namespace u5e {
  /**
   * u5e::utf8
   *
   * Handles utf8 encoded data
   */
    
  class utf8 {
  public:
    typedef char encoded_unit;
    
    template <typename UnderlyingString>
    using iterator = utf8_iterator<typename UnderlyingString::iterator>;

    template <typename UnderlyingString>
    using const_iterator = utf8_const_iterator<typename UnderlyingString::const_iterator>;

    template <typename UnderlyingStreamBuf>
    static codepoint_traits::int_type streambuf_sgetc(UnderlyingStreamBuf& in) {
      // XXX: if gptr() was not protected, this would be way easier.
      encoded_unit first_octet = in.sgetc();
      if ((first_octet & 0b10000000) == 0) {
        return first_octet;
      } else {
        int size = utf8_utils::codepoint_size(first_octet);
        int size_copy = size;
        unsigned char mask_first_octet = ~(0xFF<<(7-size));
        codepoint_traits::int_type value = (first_octet & mask_first_octet);
        while (--size) {
          encoded_unit next_octet = in.snextc();
          value = value<<6 | (next_octet & 0b00111111);
        }
        // rewind characters.
        while (--size_copy) {
          in.sungetc();
        }
        return value;
      }
    }

    template <typename UnderlyingStreamBuf>
    static codepoint_traits::int_type streambuf_snextc(UnderlyingStreamBuf& in) {
      // XXX: if gptr() was not protected, this would be way easier.
      encoded_unit first_octet = in.sgetc();
      if ((first_octet & 0b10000000) != 0) {
        int size = utf8_utils::codepoint_size(first_octet);
        while (size--) {
          in.snextc();
        }
      } else {
        in.snextc();
      }
      return streambuf_sgetc(in);
    }
    
  };
}

#endif
