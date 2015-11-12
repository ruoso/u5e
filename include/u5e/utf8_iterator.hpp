#ifndef INCLUDED_U5E_UTF8_ITERATOR
#define INCLUDED_U5E_UTF8_ITERATOR

#include <cmath>
#include <iterator>
#include <u5e/codepoint.hpp>
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
  class utf8_iterator_base {
  protected:
    iterator_assertion<std::iterator_traits<WRAPPEDITERATOR>, char> _assertions;
    WRAPPEDITERATOR raw_iterator_;

  public:
    typedef codepoint value_type;
    typedef const codepoint& reference;
    typedef int difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;
        
    inline utf8_iterator_base(const WRAPPEDITERATOR raw_iterator)
      : raw_iterator_(raw_iterator) { };

    inline void forward_one_codepoint() {
      difference_type size = codepoint_size(*raw_iterator_);
      raw_iterator_ += size;
    }
    
    inline bool rewind_to_start_of_codepoint(const char current_octet) {
      // when we do '*it = codepoint', we will leave the iterator
      // halfway into the next character
      if (__builtin_clz(~((current_octet)<<24)) == 1) {
        while ((*(raw_iterator_) & 0b11000000) == 0b10000000) {
          raw_iterator_--;
        }
        return true;
      } else {
        return false;
      }
    }

    inline void rewind_one_codepoint() {
      rewind_to_start_of_codepoint(*raw_iterator_);
      raw_iterator_--;
      while ((*(raw_iterator_) & 0b11000000) == 0b10000000) {
        raw_iterator_--;
      }
    }

    static inline int codepoint_size(const char first_octet) {
      // count leading zeros on bitwise negated first octet.  for
      // single-octet codepoints, this would return 0, so we do
      // std::max for 1 for those cases.
      return std::max(__builtin_clz(~(first_octet << 24)),1);
    }
    
    const codepoint current_codepoint() {
      char first_octet = *raw_iterator_;
      if ((first_octet & 0b10000000) == 0) {
        return first_octet;
      } else {
        if (rewind_to_start_of_codepoint(first_octet)) {
          first_octet = *raw_iterator_;
        }
        WRAPPEDITERATOR copy_ = raw_iterator_;
        difference_type size = codepoint_size(first_octet);
        unsigned char mask_first_octet = ~(0xFF<<(7-size));
        codepoint value = (first_octet & mask_first_octet);
        while (--size) {
          value = value<<6 | (*(++copy_) & 0b00111111);
        }
        return value;
      }
    }

  };

  template <typename WRAPPEDITERATOR>
  class utf8_const_iterator
    : public utf8_iterator_base<WRAPPEDITERATOR> {
  public:
    typedef utf8_const_iterator pointer;

    inline utf8_const_iterator(const WRAPPEDITERATOR raw_iterator)
      : utf8_iterator_base<WRAPPEDITERATOR>(raw_iterator) { };
    
    inline utf8_const_iterator(const utf8_const_iterator& tocopy)
      : utf8_iterator_base<WRAPPEDITERATOR>(tocopy.raw_iterator_) { };

    inline utf8_const_iterator& operator++() {
      this->forward_one_codepoint();
      return *this;
    }

    inline utf8_const_iterator operator++(int junk) {
      utf8_const_iterator copy(this->raw_iterator_);
      ++(*this);
      return copy;
    }
    
    inline utf8_const_iterator& operator--() {
      this->rewind_one_codepoint();
      return *this;
    }

    inline utf8_const_iterator operator--(int junk) {
      utf8_const_iterator copy(this->raw_iterator_);
      --(*this);
      return copy;
    }

    inline bool operator==(const utf8_const_iterator& rhs) const {
      return this->raw_iterator_ == rhs.raw_iterator_;
    }
    
    inline bool operator!=(const utf8_const_iterator& rhs) const {
      return this->raw_iterator_ != rhs.raw_iterator_;
    }

    inline const codepoint operator*() {
      return this->current_codepoint();
    }

  };

  template <typename WRAPPEDITERATOR>
  class utf8_iterator
    : public utf8_iterator_base<WRAPPEDITERATOR> {
  public:
    typedef utf8_iterator pointer;

    inline utf8_iterator(const WRAPPEDITERATOR raw_iterator)
      : utf8_iterator_base<WRAPPEDITERATOR>(raw_iterator) {};
    
    inline utf8_iterator(const utf8_iterator& tocopy)
      : utf8_iterator_base<WRAPPEDITERATOR>(tocopy.raw_iterator_) {};

    inline utf8_iterator& operator++() {
      this->forward_one_codepoint();
      return *this;
    }

    inline utf8_iterator operator++(int junk) {
      utf8_iterator copy(this->raw_iterator_);
      ++(*this);
      return copy;
    }
    
    inline utf8_iterator& operator--() {
      this->rewind_one_codepoint();
      return *this;
    }

    inline utf8_iterator operator--(int junk) {
      utf8_iterator copy(this->raw_iterator_);
      --(*this);
      return copy;
    }

    inline bool operator==(const utf8_iterator& rhs) const {
      return this->raw_iterator_ == rhs.raw_iterator_;
    }
    
    inline bool operator!=(const utf8_iterator& rhs) const {
      return this->raw_iterator_ != rhs.raw_iterator_;
    }

    class proxyobject {
    private:
      utf8_iterator<WRAPPEDITERATOR>& ref;
    public:
      proxyobject(utf8_iterator<WRAPPEDITERATOR>& refin)
        :ref(refin) { };
      operator const int() const {
        return ref.current_codepoint();
      }
      bool operator==(const codepoint value) const {
        return ref.current_codepoint() == value;
      }
      proxyobject& operator=(const codepoint value) {
        int size = std::ceil((float)(32 - __builtin_clz(value)) / (float)6);
        if (size <= 1) {
          *(ref.raw_iterator_) = (value & 0xFF);
        } else {
          unsigned char first_octet = (0xFF<<(8-size));
          first_octet |= ((value>>((size-1)*6)) & 0xFF);
          *(ref.raw_iterator_) = first_octet;
          ref.raw_iterator_++;
          while (--size) {
            unsigned char octet = 0b10000000;
            octet |= ((value>>((size-1)*6)) & 0b00111111);
            *(ref.raw_iterator_) = octet;
            ref.raw_iterator_++;
          }
        }
        return *this;
      }
    };

    // non const version returns a proxy object
    inline proxyobject operator*() {
      return proxyobject(*this);
    }

  };
 

};

#endif
