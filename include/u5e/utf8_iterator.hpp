#ifndef INCLUDED_U5E_UTF8_ITERATOR
#define INCLUDED_U5E_UTF8_ITERATOR

#include <u5e/utf8_utils.hpp>
#include <u5e/iterator_assertion.hpp>

namespace u5e {
  /**
   * u5e::utf8_iterator
   * 
   * Iterates over codepoints on utf8 data
   */
  template <typename WRAPPEDITERATOR>
  class utf8_iterator {
     iterator_assertion<WRAPPEDITERATOR,
                        char,
                        std::is_class<WRAPPEDITERATOR>::value,
                        std::is_pointer<WRAPPEDITERATOR>::value>
     _assertions;

  public:
    typedef codepoint value_type;
    typedef codepoint& reference;
    typedef utf8_iterator pointer;
    typedef int difference_type;
    typedef std::forward_iterator_tag iterator_category;
        
    inline utf8_iterator(const WRAPPEDITERATOR raw_iterator)
      : raw_iterator_(raw_iterator) { };
    
    inline utf8_iterator(const utf8_iterator& tocopy)
      : raw_iterator_(tocopy.raw_iterator_) { };
    
    inline utf8_iterator operator++(int junk) {
      utf8_iterator copy(raw_iterator_);
      char octet = *raw_iterator_;
      int size = utf8_utils::codepoint_size(octet);
      raw_iterator_ += size;
      return copy;
    }
    
    inline utf8_iterator operator++() {
      difference_type size = utf8_utils::codepoint_size(*raw_iterator_);
      raw_iterator_ += size;
      return *this;
    }
    
    inline codepoint operator*() {
      WRAPPEDITERATOR copy = raw_iterator_;
      char octets[utf8_utils::max_codepoint_size];
      std::memset(octets, 0, utf8_utils::max_codepoint_size);
      
      octets[0] = *copy++;
      difference_type size = utf8_utils::codepoint_size(octets[0]);
      for (int i = 1; i < size; i++) {
        octets[i] = *copy++;
      }
      return utf8_utils::octets_to_codepoint(octets, size);
    }
    
    inline bool operator==(const utf8_iterator& rhs) const { return raw_iterator_ == rhs.raw_iterator_; }
    inline bool operator!=(const utf8_iterator& rhs) const { return raw_iterator_ != rhs.raw_iterator_; }

  private:
    WRAPPEDITERATOR raw_iterator_;
  };
 

};

#endif
