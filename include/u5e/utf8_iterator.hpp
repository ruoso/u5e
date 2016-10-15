#ifndef INCLUDED_U5E_UTF8_ITERATOR
#define INCLUDED_U5E_UTF8_ITERATOR

#include <cmath>
#include <iterator>
#include <u5e/codepoint.hpp>
#include <u5e/iterator_assertion.hpp>

namespace u5e {
  /**
   * u5e::utf8_iterator_base
   * 
   * Defines the basic inner workings of both the const and the non
   * const iterators.
   *
   * \tparam WRAPPEDITERATOR The underlying type to be iterated over.
   */
  template <typename WRAPPEDITERATOR>
  class utf8_iterator_base {
  protected:
    /**
     * The WRAPPEDITERATOR must match the attributes of char
     */
    iterator_assertion<WRAPPEDITERATOR, char> _assertions;
    /**
     * This class composes over the WRAPPEDITERATOR
     */
    WRAPPEDITERATOR raw_iterator_;

  public:
    //@{
    /**
     * Basic iterator typedefs
     */
    typedef codepoint value_type;
    typedef const codepoint& reference;
    typedef int difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;
    //@}

    /**
     * Create a iterator from the underlying iterator
     */
    inline utf8_iterator_base(const WRAPPEDITERATOR raw_iterator)
      : raw_iterator_(raw_iterator) { };

    inline int codepoint_size(const char first_octet) {
      // count leading zeros on bitwise negated first octet.  for
      // single-octet codepoints, this would return 0, so we do
      // std::max for 1 for those cases.
      return std::max(__builtin_clz(~(first_octet << 24)),1);
    }

    /**
     * Advance the iterator to the next codepoint
     */
    inline void forward_one_codepoint() {
      difference_type size = codepoint_size(*raw_iterator_);
      std::advance(raw_iterator_, size);
    }
    
    /**
     * When doing a reverse itetor, you need to be able to find
     * where the current codepoint started.
     */
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

    /**
     * Go to the previous codepoint.
     */
    inline void rewind_one_codepoint() {
      rewind_to_start_of_codepoint(*raw_iterator_);
      raw_iterator_--;
      while ((*(raw_iterator_) & 0b11000000) == 0b10000000) {
        raw_iterator_--;
      }
    }
    
    /**
     * Return the codepoint that starts where we are now
     */
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
        int value = (first_octet & mask_first_octet);
        while (--size) {
          value = value<<6 | (*(++copy_) & 0b00111111);
        }
        return value;
      }
    }

  };

  /**
   * utf8_const_iterator
   *
   * Offer a read-only iterator for utf8 encoded strings.
   */
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

  /**
   * utf8_iterator is a mutable iterator.
   *
   * Note that if you set a value in the middle of a text, you will
   * likely make the string invalid. Most of the time you should only
   * consider appending to an iterator, never writing in the middle of
   * the text.
   */
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

    class proxyobject : public codepoint {
    private:
      utf8_iterator<WRAPPEDITERATOR>& ref;
    public:
      proxyobject(utf8_iterator<WRAPPEDITERATOR>& refin)
        :ref(refin) {
        utf8_iterator<WRAPPEDITERATOR> copy = refin;
        value = copy.current_codepoint().value;
      };
      proxyobject& operator=(const codepoint c) {
        int value = c.value; // operate on codepoint as integer
        int size = std::ceil((float)(32 - __builtin_clz(value)) / (float)6);
        if (size <= 1) {
          *(ref.raw_iterator_) = (value & 0xFF);
        } else {
          utf8_iterator<WRAPPEDITERATOR> copy = ref;
          unsigned char first_octet = (0xFF<<(8-size));
          first_octet |= ((value>>((size-1)*6)) & 0xFF);
          *(copy.raw_iterator_) = first_octet;
          copy.raw_iterator_++;
          while (--size) {
            unsigned char octet = 0b10000000;
            octet |= ((value>>((size-1)*6)) & 0b00111111);
            *(copy.raw_iterator_) = octet;
            copy.raw_iterator_++;
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
