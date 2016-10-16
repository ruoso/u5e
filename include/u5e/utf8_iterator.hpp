#ifndef INCLUDED_U5E_UTF8_ITERATOR
#define INCLUDED_U5E_UTF8_ITERATOR

#include <cmath>
#include <iterator>
#include <u5e/codepoint.hpp>
#include <u5e/iterator_assertion.hpp>

namespace u5e {
  /**
   * \brief Defines the basic inner workings of utf8 iterator
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

    /**
     * Find the codepoint size given the first utf8 octet
     */
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
   * \brief const iterator for utf8 encoded strings.
   * \tparam WRAPPEDITERATOR The underlying type to be iterated over.
   */
  template <typename WRAPPEDITERATOR>
  class utf8_const_iterator
    : public utf8_iterator_base<WRAPPEDITERATOR> {
  public:
    /**
     * Offers itself as the pointer type
     */
    typedef utf8_const_iterator pointer;

    /**
     * Create from the underlying iterator type
     */
    inline utf8_const_iterator(const WRAPPEDITERATOR raw_iterator)
      : utf8_iterator_base<WRAPPEDITERATOR>(raw_iterator) { };

    /**
     * Copy constructor
     */
    inline utf8_const_iterator(const utf8_const_iterator& tocopy)
      : utf8_iterator_base<WRAPPEDITERATOR>(tocopy.raw_iterator_) { };

    //@{
    /**
     * Advance the iterator
     */
    inline utf8_const_iterator& operator++() {
      this->forward_one_codepoint();
      return *this;
    }

    inline utf8_const_iterator operator++(int junk) {
      utf8_const_iterator copy(this->raw_iterator_);
      ++(*this);
      return copy;
    }
    //@}

    //@{
    /**
     * Rewinds the iterator
     */
    inline utf8_const_iterator& operator--() {
      this->rewind_one_codepoint();
      return *this;
    }

    inline utf8_const_iterator operator--(int junk) {
      utf8_const_iterator copy(this->raw_iterator_);
      --(*this);
      return copy;
    }
    //@}

    //@{
    /**
     * Compare with another iterator
     */
    inline bool operator==(const utf8_const_iterator& rhs) const {
      return this->raw_iterator_ == rhs.raw_iterator_;
    }
    
    inline bool operator!=(const utf8_const_iterator& rhs) const {
      return this->raw_iterator_ != rhs.raw_iterator_;
    }
    //@}

    /**
     * Dereference the current codepoint out of the iterator
     */
    inline const codepoint operator*() {
      return this->current_codepoint();
    }

  };

  /**
   * \brief mutable utf8 iterator
   *
   * Note that if you set a value in the middle of a text, you will
   * likely make the string invalid. Most of the time you should only
   * consider appending to an iterator, never writing in the middle of
   * the text.
   * \tparam WRAPPEDITERATOR The underlying type to be iterated over.
   */
  template <typename WRAPPEDITERATOR>
  class utf8_iterator
    : public utf8_iterator_base<WRAPPEDITERATOR> {
  public:
    /**
     * Offer itself as the pointer type
     */
    typedef utf8_iterator pointer;

    /**
     * Construct fro the underlying iterator
     */
    inline utf8_iterator(const WRAPPEDITERATOR raw_iterator)
      : utf8_iterator_base<WRAPPEDITERATOR>(raw_iterator) {};

    /**
     * Copy constructor
     */
    inline utf8_iterator(const utf8_iterator& tocopy)
      : utf8_iterator_base<WRAPPEDITERATOR>(tocopy.raw_iterator_) {};

    //@{
    /**
     * Advance the iterator
     */
    inline utf8_iterator& operator++() {
      this->forward_one_codepoint();
      return *this;
    }

    inline utf8_iterator operator++(int junk) {
      utf8_iterator copy(this->raw_iterator_);
      ++(*this);
      return copy;
    }
    //@}

    //@{
    /**
     * Rewind the iterator
     */
    inline utf8_iterator& operator--() {
      this->rewind_one_codepoint();
      return *this;
    }

    inline utf8_iterator operator--(int junk) {
      utf8_iterator copy(this->raw_iterator_);
      --(*this);
      return copy;
    }
    //@}

    //@{
    /**
     * Compare the iterator with another iterator
     */
    inline bool operator==(const utf8_iterator& rhs) const {
      return this->raw_iterator_ == rhs.raw_iterator_;
    }
    
    inline bool operator!=(const utf8_iterator& rhs) const {
      return this->raw_iterator_ != rhs.raw_iterator_;
    }
    //@}

    /**
     * \brief offers write access to the iterator at a given position
     *
     * This is necessary because operator= can only be done after
     * operator* is executed, this wouldn't be necessary if there was
     * a dedicated operator for 'assign to the dereference'.
     */
    class proxyobject : public codepoint {
    private:
      /**
       * A proxy object refers to an iterator state
       */
      utf8_iterator<WRAPPEDITERATOR>& ref;
    public:
      
      /**
       * Create from the iterator
       */
      proxyobject(utf8_iterator<WRAPPEDITERATOR>& refin)
        :ref(refin) {
        utf8_iterator<WRAPPEDITERATOR> copy = refin;
        value = copy.current_codepoint().value;
      };

      /**
       * Assign a codepoint to this position, writing as many octets
       * as necessary. Note that if you do this in the middle of a
       * string, there is a likely chance that you will render the
       * remainder of the string invalid. So it's really only a good
       * idea to do this as an "append" operation.
       */
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

    /**
     * mutable utf8 iterator returns a proxy object in order to allow
     * assignment to happen.
     */
    inline proxyobject operator*() {
      return proxyobject(*this);
    }
   
  };
};

#endif
