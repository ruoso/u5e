#ifndef INCLUDED_U5E_UTF8
#define INCLUDED_U5E_UTF8

#include <iterator>
#include <cstring>
#include <type_traits>
#include <u5e/codepoint.hpp>

namespace u5e {
  /**
   * u5e::utf8
   *
   * Handles utf8 encoded data
   */
    
  template <typename BUFFERTYPE>
  class utf8 {
  public:
    static_assert(sizeof(typename BUFFERTYPE::value_type)==sizeof(char),
                  "sizeof BUFFERTYPE::value_type incompatible with utf8");
    static_assert(alignof(typename BUFFERTYPE::value_type)==alignof(char),
                  "alignof BUFFERTYPE::value_type incompatible with utf8");
    static_assert(std::is_integral<typename BUFFERTYPE::value_type>::value,
                  "BUFFERTYPE::value_type is not an integral type");

    // value_type is always codepoint
    typedef codepoint value_type;
    // pointer to encoded_buffer
    typedef utf8<BUFFERTYPE>* pointer;
    // const pointer to encoded_buffer
    typedef const utf8<BUFFERTYPE>* const_pointer;
    // reference to encoded_buffer
    typedef utf8<BUFFERTYPE>& reference;
    // size type is always size_t, regardless of encoding, in order to
    // isolate the knowledge of the encoding from the user code
    typedef std::size_t size_type;
    // difference type is always ptrdiff_t, regardrless of encoding,
    // in order to isolate the knowledge of the encoding from the user
    // code
    typedef std::ptrdiff_t difference_type;

    static const typename BUFFERTYPE::size_type min_codepoint_size = 1;
    static const typename BUFFERTYPE::size_type max_codepoint_size = 6;
    static const typename BUFFERTYPE::size_type max_bmp_codepoint_size = 3;
    static const typename BUFFERTYPE::size_type max_ascii_codepoint_size = 1;

    // TODO - XXX - Actually implement this
    typedef typename BUFFERTYPE::reverse_iterator reverse_iterator;

    // TODO - XXX - Actually implement this
    typedef typename BUFFERTYPE::const_iterator const_iterator;

    // TODO - XXX - Actually implement this
    typedef typename BUFFERTYPE::const_reverse_iterator const_reverse_iterator;
    
    // forward declare
    class iterator;

    /**
     * Constructors
     */
    utf8() = default;
    utf8(const BUFFERTYPE& raw_buffer)
      : raw_buffer(raw_buffer) { };
    utf8<BUFFERTYPE>& operator= (const utf8<BUFFERTYPE> &other) = delete;

    inline iterator begin() {
      return iterator(raw_buffer.begin());
    }
    
    inline iterator end() {
      return iterator(raw_buffer.end());
    }
    
  private:
    // raw buffer as specified by the storage type
    BUFFERTYPE raw_buffer;

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
      typename BUFFERTYPE::iterator raw_iterator_;
      
    public:
      inline iterator(const typename BUFFERTYPE::iterator raw_iterator)
        : raw_iterator_(raw_iterator) { };
      
      inline iterator(const iterator& tocopy)
        : raw_iterator_(tocopy.raw_iterator_) { };

      inline iterator operator++(int junk) {
        iterator copy(raw_iterator_);
        char octet = *raw_iterator_;
        int size = codepoint_size(octet);
        raw_iterator_ += size;
        return copy;
      }

      inline iterator operator++() {
        difference_type size = codepoint_size(*raw_iterator_);
        raw_iterator_ += size;
        return *this;
      }

      inline codepoint operator*() {
        typename BUFFERTYPE::iterator copy = raw_iterator_;
        char octets[max_codepoint_size];
        std::memset(octets, 0, max_codepoint_size);
        
        octets[0] = *copy++;
        difference_type size = codepoint_size(octets[0]);
        for (int i = 1; i < size; i++) {
          octets[i] = *copy++;
        }
        return octets_to_codepoint(octets, size);
      }
        
      inline bool operator==(const iterator& rhs) const { return raw_iterator_ == rhs.raw_iterator_; }
      inline bool operator!=(const iterator& rhs) const { return raw_iterator_ != rhs.raw_iterator_; }
    };
      
  };
}

#endif
