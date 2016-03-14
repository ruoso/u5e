#ifndef INCLUDED_U5E_UTF8
#define INCLUDED_U5E_UTF8

#include <iterator>
#include <cstring>
#include <type_traits>
#include <u5e/codepoint.hpp>
#include <u5e/encoding_assertion.hpp>
#include <u5e/utf8_iterator.hpp>

namespace u5e {
  /**
   * u5e::utf8
   *
   * Handles utf8 encoded data
   */
    
  template <typename BUFFERTYPE>
  class utf8 {
    encoding_assertion<BUFFERTYPE, char> _assertion;
  public:

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

    // TODO - XXX - Actually implement this
    typedef typename BUFFERTYPE::reverse_iterator reverse_iterator;
    // TODO - XXX - Actually implement this
    typedef typename BUFFERTYPE::const_reverse_iterator const_reverse_iterator;
    
    typedef utf8_iterator<typename BUFFERTYPE::iterator> iterator;

    typedef utf8_const_iterator<typename BUFFERTYPE::const_iterator> const_iterator;

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

    inline const_iterator cbegin() {
      return const_iterator(raw_buffer.cbegin());
    }
    
    inline const_iterator cend() {
      return const_iterator(raw_buffer.cend());
    }
    
  private:
    // raw buffer as specified by the storage type
    BUFFERTYPE raw_buffer;
  };
}

#endif
