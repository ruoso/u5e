#ifndef INCLUDED_U5E_ENCODED_BUFFER_HPP
#define INCLUDED_U5E_ENCODED_BUFFER_HPP

#include <iterator>

#include <u5e/buffer.hpp>
#include <u5e/codepoint.hpp>

namespace u5e {

  /**
   * u5e::encoded_buffer
   *
   * This is the basic interface for dealing with codepoints, it
   * composes with the specific encoding in order to traverse the data
   * back and forth.
   *
   * This is modelled after string_view for familiar semantics.
   *
   * When traversing this buffer, you will not risk splitting a
   * unicode codepoint in two, however, you will still risk splitting
   * a grapheme in two.
   */
  template <class EncodingT>
  class encoded_buffer {
    /**
     * Member types
     */

    // the encoding of the raw_buffer
    typedef EncodingT encoding_type;
    // value_type is always codepoint
    typedef codepoint value_type;
    // pointer to encoded_buffer
    typedef encoded_buffer<EncodingT>* pointer;
    // const pointer to encoded_buffer
    typedef const encoded_buffer<EncodingT>* const_pointer;
    // reference to encoded_buffer
    typedef encoded_buffer<EncodingT>& reference;
    // iterator, delegated to the encoding
    typedef EncodingT::enc_iterator_type iterator;
    // const iterator, delegated to the encoding
    typedef EncodingT::enc_iterator_type const_iterator;
    // reverse iterator, delegated to the encoding
    typedef EncodingT::enc_reverse_iterator_type reverse_iterator;
    // reverse const iterator, delegated to the encoding
    typedef EncodingT::enc_reverse_iterator_type const_reverse_iterator;
    // const reference to encoded_buffer
    typedef const encoded_buffer<EncodingT>& const_reference;
    // size type is always size_t, regardless of encoding, in order to
    // isolate the knowledge of the encoding from the user code
    typedef std::size_t size_type;
    // difference type is always ptrdiff_t, regardrless of encoding,
    // in order to isolate the knowledge of the encoding from the user
    // code
    typedef std::ptrdiff_t difference_type;

    /**
     * Member attributes
     */
    // raw buffer as specified by the encoding
    const EncodingT::enc_buffer_type raw_buffer;

    /**
     * Constructors
     */
    constexpr encoded_buffer() = default;
    constexpr encoded_buffer(const encoded_buffer& other) = default;
    constexpr encoded_buffer(const EncodingT::enc_buffer_type raw_buffer)
      : raw_buffer(raw_buffer) { };
    encoded_buffer& operator= (const encoded_buffer &other) = delete;
    
    /**
     * Member functions
     */
    
  };

}

#endif
