#ifndef INCLUDED_U5E_UTF8_ITERATOR
#define INCLUDED_U5E_UTF8_ITERATOR

#include <cmath>
#include <iterator>
#include <u5e/codepoint.hpp>
#include <u5e/iterator_assertion.hpp>
#include <u5e/utf8_util.hpp>

namespace u5e {
  /**
   * \brief Defines the basic inner workings of utf8 iterator
   *
   * \tparam NativeIterator The underlying type to be iterated over.
   */
  template <typename NativeIterator>
  class utf8_iterator_base {
  public:
    /**
     * The NativeIterator must match the attributes of char
     */
    iterator_assertion<NativeIterator, char> _assertions;
    /**
     * This class composes over the NativeIterator
     */
    NativeIterator raw_iterator_;

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
    inline utf8_iterator_base(const NativeIterator raw_iterator)
      : raw_iterator_(raw_iterator) {
    };

    /**
     * Advance the iterator to the next codepoint
     */
    inline void forward_one_codepoint() {
      difference_type size = utf8_util::codepoint_size(*raw_iterator_);
      std::advance(raw_iterator_, size);
    }
    
    /**
     * When doing a reverse itetor, you need to be able to find
     * where the current codepoint started.
     */
    inline bool rewind_to_start_of_codepoint(const char current_octet) {
      // when we do '*it = codepoint', we will leave the iterator
      // halfway into the next character
      bool ret = false;
      while (utf8_util::is_codepoint_continuation(*raw_iterator_)) {
        raw_iterator_--;
        ret = true;
      }
      return ret;
    }

    /**
     * Go to the previous codepoint.
     */
    inline void rewind_one_codepoint() {
      rewind_to_start_of_codepoint(*raw_iterator_);
      raw_iterator_--;
      while (utf8_util::is_codepoint_continuation(*raw_iterator_)) {
        raw_iterator_--;
      }
    }
    
    /**
     * Return the codepoint that starts where we are now
     */
    const codepoint current_codepoint() {
      char first_octet = *raw_iterator_;
      if (utf8_util::is_7bit_character(first_octet)) {
        return first_octet;
      } else {
        if (rewind_to_start_of_codepoint(first_octet)) {
          first_octet = *raw_iterator_;
        }
        NativeIterator copy_ = raw_iterator_;
        difference_type size =
          utf8_util::codepoint_size(first_octet);
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
   * \tparam NativeIterator The underlying type to be iterated over.
   */
  template <typename NativeIterator>
  class utf8_const_iterator
    : public utf8_iterator_base<NativeIterator> {
  public:
    /**
     * Offers itself as the pointer type
     */
    typedef utf8_const_iterator pointer;

    /**
     * Create from the underlying iterator type
     */
    inline utf8_const_iterator(const NativeIterator raw_iterator)
      : utf8_iterator_base<NativeIterator>(raw_iterator) { };

    /**
     * Copy constructor
     */
    inline utf8_const_iterator(const utf8_const_iterator& tocopy)
      : utf8_iterator_base<NativeIterator>(tocopy.raw_iterator_) { };

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
      char c;
      utf8_const_iterator copy(*this);
      c = *(copy.raw_iterator_);
      copy.rewind_to_start_of_codepoint(c);
      c = *(copy.raw_iterator_);
      int size = utf8_util::codepoint_size(c);
      while (size) {
        if (copy.raw_iterator_ == rhs.raw_iterator_) {
          return true;
        }
        ++(copy.raw_iterator_);
        --size;
      }
      return false;
    }
    
    inline bool operator!=(const utf8_const_iterator& rhs) const {
      return !(*this == rhs);
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
   * \tparam NativeIterator The underlying type to be iterated over.
   */
  template <typename NativeIterator>
  class utf8_iterator
    : public utf8_iterator_base<NativeIterator> {
  public:
    /**
     * Offer itself as the pointer type
     */
    typedef utf8_iterator pointer;

    /**
     * Construct fro the underlying iterator
     */
    inline utf8_iterator(const NativeIterator raw_iterator)
      : utf8_iterator_base<NativeIterator>(raw_iterator) {};

    /**
     * Copy constructor
     */
    inline utf8_iterator(const utf8_iterator& tocopy)
      : utf8_iterator_base<NativeIterator>(tocopy.raw_iterator_) {};

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
      char c;
      utf8_iterator copy(*this);
      c = *(copy.raw_iterator_);
      copy.rewind_to_start_of_codepoint(c);
      c = *(copy.raw_iterator_);
      int size = utf8_util::codepoint_size(c);
      while (size) {
        if (copy.raw_iterator_ == rhs.raw_iterator_) {
          return true;
        }
        ++(copy.raw_iterator_);
        --size;
      }
      return false;
    }
    
    inline bool operator!=(const utf8_iterator& rhs) const {
      return !(*this == rhs);
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
      utf8_iterator<NativeIterator>& ref;
    public:
      
      /**
       * Create from the iterator
       */
      proxyobject(utf8_iterator<NativeIterator>& refin)
        :ref(refin) {
        utf8_iterator<NativeIterator> copy = refin;
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
        int size = utf8_util::encoded_size(value);
        if (size <= 1) {
          *(ref.raw_iterator_) = (value & 0xFF);
        } else {
          unsigned char first_octet = (0xFF<<(8-size));
          first_octet |= ((value>>((size-1)*6)) & 0xFF);
          *(ref.raw_iterator_) = first_octet;
          while (--size) {
            unsigned char octet = 0b10000000;
            octet |= ((value>>((size-1)*6)) & 0b00111111);
            ref.raw_iterator_++;
            *(ref.raw_iterator_) = octet;
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
