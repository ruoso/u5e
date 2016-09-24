#ifndef INCLUDED_U5E_BASIC_ENCODEDSTRING
#define INCLUDED_U5E_BASIC_ENCODEDSTRING

#include <u5e/codepoint.hpp>
#include <u5e/codepoint_traits.hpp>

namespace u5e {

  /**
   * u5e::basic_encodedstring is the encoding-aware alternative to
   * basic_string. However, in order to avoid re-implementing string,
   * this always wraps an underlying string type.
   *
   * * Encoding: Text is always represented in a specific encoding,
   *   there is no such thing as a "natural", or "native"
   *   representation of text, for that reason, the encoding is a part
   *   of the type.
   *
   * * UnderlyingString: In order to re-use the string support, this
   *   will always be implemented as a wrapper around an underlying
   *   string type. The idea is that the C++ string libraries operate
   *   on unencoded memory, while the u5e types offer a layer on top
   *   of that for the purposes of implementing unicode in a type-safe
   *   way. Note that this applies to any 'string-like' object, such
   *   as string or string_view.
   */
  template <typename Encoding,
            typename UnderlyingString>
  class basic_encodedstring {
  public:
    /**
     * We offer an interface similar to basic_string
     */
    typedef u5e::codepoint_traits                       traits_type;
    typedef u5e::codepoint                              value_type;
    typedef typename UnderlyingString::allocator_type   allocator_type;
    typedef u5e::codepoint_traits::pos_type             size_type;
    typedef u5e::codepoint_traits::off_type             difference_type;
    typedef value_type&                                 reference;
    typedef const value_type&                           const_reference;
    typedef typename UnderlyingString::pointer          pointer;
    typedef typename UnderlyingString::const_pointer    const_pointer;
    typedef typename Encoding::template iterator<UnderlyingString>
                                                        iterator;
    typedef typename Encoding::template const_iterator<UnderlyingString>
                                                        const_iterator;
    typedef std::reverse_iterator<iterator>             reverse_iterator;
    typedef std::reverse_iterator<const_iterator>       const_reverse_iterator;

    /**
     * Constructors
     */
    basic_encodedstring() = default;

    basic_encodedstring(const UnderlyingString& s)
      : underlying_string(s) { };

    basic_encodedstring<Encoding, UnderlyingString>&
    operator= (const basic_encodedstring<Encoding, UnderlyingString> &other)
    = delete;
    
    inline iterator begin() {
      return iterator(underlying_string.begin());
    }
    
    inline iterator end() {
      return iterator(underlying_string.end());
    }

    inline const_iterator cbegin() {
      return const_iterator(underlying_string.cbegin());
    }
    
    inline const_iterator cend() {
      return const_iterator(underlying_string.cend());
    }
    
  private:
    // raw buffer as specified by the storage type
    UnderlyingString underlying_string;
  };
    
}

#endif
