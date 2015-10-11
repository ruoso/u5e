#ifndef INCLUDED_U5E_ENC_UTF8
#define INCLUDED_U5E_ENC_UTF8

#include <string.h>
#include <u5e/buffer.hpp>
#include <u5e/codepoint.hpp>

namespace u5e {
  namespace enc {
    
    /**
     * u5e::enc::utf8
     *
     * Handles utf8 encoded data
     */
    
    class utf8 {
    public:
      typedef u5e::buffer<char> enc_buffer_type;
      static const enc_buffer_type::size_type min_codepoint_size = 1;
      static const enc_buffer_type::size_type max_codepoint_size = 6;
      static const enc_buffer_type::size_type max_bmp_codepoint_size = 3;
      static const enc_buffer_type::size_type max_ascii_codepoint_size = 1;

      // TODO - XXX - Actually implement this
      typedef enc_buffer_type::reverse_iterator reverse_iterator;

      // forward declare
      class iterator;

    private:
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

    public:
      class iterator {
      public:
        typedef codepoint value_type;
        typedef codepoint& reference;
        typedef iterator pointer;
        typedef int difference_type;
        typedef std::forward_iterator_tag iterator_category;
        
      private:
        enc_buffer_type::iterator raw_iterator_;
        
      public:
        iterator(const enc_buffer_type::iterator& raw_iterator)
          : raw_iterator_(raw_iterator) { };

        iterator(const iterator& tocopy)
          : raw_iterator_(tocopy.raw_iterator_) { };

        iterator operator++() {
          iterator copy(raw_iterator_);
          char octet = *raw_iterator_;
          int size = codepoint_size(octet);
          raw_iterator_ += size;
          return copy;
        }

        iterator operator++(int junk) {
          difference_type size = codepoint_size(*raw_iterator_);
          raw_iterator_ += size;
          return *this;
        }

        const codepoint operator*() {
          enc_buffer_type::iterator copy = raw_iterator_;
          char octets[max_codepoint_size];
          memset(octets, 0, max_codepoint_size);

          octets[0] = *copy++;
          difference_type size = codepoint_size(octets[0]);
          for (int i = 1; i < size; i++) {
            octets[i] = *copy++;
          }
          return octets_to_codepoint(octets, size);
        }
        
        bool operator==(const iterator& rhs) { return raw_iterator_ == rhs.raw_iterator_; }
        bool operator!=(const iterator& rhs) { return raw_iterator_ != rhs.raw_iterator_; }
      };
      
      static inline u5e::enc::utf8::iterator begin(enc_buffer_type raw_buffer) {
        return u5e::enc::utf8::iterator(raw_buffer.begin());
      }

      static inline u5e::enc::utf8::iterator end(enc_buffer_type raw_buffer) {
        return u5e::enc::utf8::iterator(raw_buffer.end());
      }

    };
  }
}

#endif
