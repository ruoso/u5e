#ifndef INCLUDED_U5E_UTF8_ITERATOR
#define INCLUDED_U5E_UTF8_ITERATOR

#include <iterator>
#include <u5e/iterator_assertion.hpp>

namespace u5e {
  /**
   * u5e::utf8_iterator
   * 
   * Iterates over codepoints on utf8 data.
   *
   * Since this iterator manipulates data in octets and offers
   * codepoints, it can't offer a mutable interface. For write access,
   * you need to use an utf8_output_iterator.
   */
  template <typename WRAPPEDITERATOR>
  class utf8_iterator {
    iterator_assertion<std::iterator_traits<WRAPPEDITERATOR>, char> _assertions;
  public:
    typedef codepoint value_type;
    typedef const codepoint& reference;
    typedef utf8_iterator pointer;
    typedef int difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;
        
    inline utf8_iterator(const WRAPPEDITERATOR raw_iterator)
      : raw_iterator_(raw_iterator) { };
    
    inline utf8_iterator(const utf8_iterator& tocopy)
      : raw_iterator_(tocopy.raw_iterator_) { };
    
    inline utf8_iterator operator++() {
      difference_type size = codepoint_size(*raw_iterator_);
      raw_iterator_ += size;
      return *this;
    }

    inline utf8_iterator operator++(int junk) {
      utf8_iterator copy(raw_iterator_);
      ++(*this);
      return copy;
    }
    
    inline utf8_iterator operator--() {
      raw_iterator_--;
      while ((*(raw_iterator_) & 0b11000000) == 0b10000000) {
        raw_iterator_--;
      }
      return *this;
    }

    inline utf8_iterator operator--(int junk) {
      utf8_iterator copy(raw_iterator_);
      --(*this);
      return copy;
    }

    static inline int codepoint_size(const char first_octet) {
      // count leading zeros on bitwise negated first octet.  for
      // single-octet codepoints, this would return 0, so we do
      // std::max for 1 for those cases.
      return std::max(__builtin_clz(~(first_octet << 24)),1);
    }

    inline codepoint operator*() {
      char first_octet = *raw_iterator_;
      difference_type size = codepoint_size(first_octet);
      if (size == 1) {
        return first_octet;
      } else {
        constexpr char mask_first_octet[6] =
          { 0b00011111, 0b00001111, 0b00000111, 0b00000011, 0b00000001 };
        constexpr char mask_other_octets = 0b00111111;
        codepoint value = (first_octet & mask_first_octet[size - 2]);
        WRAPPEDITERATOR copy_ = raw_iterator_;
        while (--size) {
          value = value<<6 | (*(++copy_) & mask_other_octets);
        }
        return value;
      }
    }
    
    inline bool operator==(const utf8_iterator& rhs) const { return raw_iterator_ == rhs.raw_iterator_; }
    inline bool operator!=(const utf8_iterator& rhs) const { return raw_iterator_ != rhs.raw_iterator_; }

  private:
    WRAPPEDITERATOR raw_iterator_;
  };
 

};

#endif
