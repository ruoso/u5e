#ifndef INCLUDED_U5E_UTF32_NATIVE_HPP
#define INCLUDED_U5E_UTF32_NATIVE_HPP

#include <type_traits>
#include <u5e/codepoint.hpp>

namespace u5e {
  /**
   * u5e::utf32_native
   *
   * The native utf32 encoding is built with the native 32 bit
   * integer type. It is specially more useful for cases where
   * you need to do extensive manipulation on text, since it
   * allows you to have constant random access time.
   */
  template <typename BUFFERTYPE>
  class utf32_native {
  public:
    static_assert(sizeof(typename BUFFERTYPE::value_type)==sizeof(int),
                  "sizeof BUFFERTYPE::value_type incompatible with utf32(n)");
    static_assert(alignof(typename BUFFERTYPE::value_type)==alignof(int),
                  "alignof BUFFERTYPE::value_type incompatible with utf32(n)");
    static_assert(std::is_integral<typename BUFFERTYPE::value_type>::value,
                  "BUFFERTYPE::value_type is not an integral type");

    // value_type is always codepoint
    typedef codepoint value_type;
    // pointer to encoded_buffer
    typedef utf32_native<BUFFERTYPE>* pointer;
    // const pointer to encoded_buffer
    typedef const utf32_native<BUFFERTYPE>* const_pointer;
    // reference to encoded_buffer
    typedef utf32_native<BUFFERTYPE>& reference;
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

    // since this is the native utf32, we can just delegate this
    typedef typename BUFFERTYPE::iterator iterator;
    typedef typename BUFFERTYPE::reverse_iterator reverse_iterator;
    typedef typename BUFFERTYPE::const_iterator const_iterator;
    typedef typename BUFFERTYPE::const_reverse_iterator const_reverse_iterator;

    /**
     * Constructors
     */
    utf32_native() = default;
    utf32_native(const BUFFERTYPE& raw_buffer)
      : raw_buffer(raw_buffer) { };
    utf32_native<BUFFERTYPE>& operator=(const utf32_native<BUFFERTYPE> &other) = delete;
    
    inline iterator begin() {
      return iterator(raw_buffer.begin());
    }
    
    inline iterator end() {
      return iterator(raw_buffer.end());
    }
    
  private:
    // raw buffer as specified by the storage type
    BUFFERTYPE raw_buffer;
  };
}

#endif
