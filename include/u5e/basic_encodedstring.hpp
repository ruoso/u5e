#ifndef INCLUDED_U5E_BASIC_ENCODEDSTRING
#define INCLUDED_U5E_BASIC_ENCODEDSTRING

#include <iterator>
#include <u5e/codepoint.hpp>
#include <u5e/codepoint_traits.hpp>

namespace u5e {
  template <typename T> class basic_grapheme_iterator;

  /**
   * \brief basic encoding support over string-like objects.
   *
   * u5e::basic_encodedstring implements encoding support on top of a
   * string-like object, it is implemented by simply wrapping the
   * native string type in order to provide a customized iterator
   * that offers codepoint-by-codepoint access instead of iterating
   * over the native type.
   *
   * \tparam Encoding Text is always represented in a specific
   *   encoding, there is no such thing as a "natural", or "native"
   *   representation of text, for that reason, the encoding is a part
   *   of the type.
   *
   * \tparam NativeString In order to re-use the string support,
   *   this will always be implemented as a wrapper around an
   *   native string-like type. The idea is that the C++ string
   *   libraries operate on unencoded memory, while the u5e types
   *   offer a layer on top of that for the purposes of implementing
   *   unicode in a type-safe way. Note that this applies to any
   *   'string-like' object, such as string or string_view.
   */
  template <typename Encoding,
            typename NativeString>
  class basic_encodedstring {
  public:
    //@{
    /**
     * Offer an interface such that the size of the thing you're
     * iterating over is a codepoint, regardless of the native
     * type.
     */
    typedef u5e::codepoint_traits                       traits_type;
    typedef u5e::codepoint                              value_type;
    typedef u5e::codepoint_traits::pos_type             size_type;
    typedef u5e::codepoint_traits::off_type             difference_type;
    typedef value_type&                                 reference;
    typedef const value_type&                           const_reference;
    typedef typename NativeString::pointer          pointer;
    typedef typename NativeString::const_pointer    const_pointer;
    //@}

    //@{
    /**
     * The Encoding template argument must provide iterator and
     * const_iterator member types. Those should iterate over
     * codepoints, regardless of the encoding and the native type.
     *
     * The iterator and const_iterator member types must be themselves
     * templates that take the NativeString type as a template
     * argument.
     */
    typedef typename Encoding::template iterator<NativeString>
    iterator;
    typedef typename Encoding::template const_iterator<NativeString>
    const_iterator;
    //@}

    //@{
    /**
     * Delegated to std::reverse_iterator
     */
    typedef std::reverse_iterator<iterator>             reverse_iterator;
    typedef std::reverse_iterator<const_iterator>       const_reverse_iterator;
    //@}
    
    /**
     * \brief Raw buffer as specified by the native type.
     *
     * This means that this class is exactly as expensive as whichever
     * native type is being used, it also means this class delegates
     * all memory management to that native type.
     *
     * This member is public because you should be able to completely
     * manage the native object if you need to.
     */
    NativeString native_string;

    /**
     * Default constructor, delegated to the native type.
     */
    basic_encodedstring() = default;

    /**
     * Implicit conversion from the native type.
     */
    basic_encodedstring(const NativeString& s)
      : native_string(s) { };

    /**
     * Assignment operator, assigns the native type.
     */
    basic_encodedstring&
    operator= (const basic_encodedstring &other) {
      native_string = other;
    }

    //@{
    /**
     * Get begin and end iterators.
     */
    inline iterator begin() {
      return iterator(native_string.begin());
    }
    inline iterator end() {
      return iterator(native_string.end());
    }
    inline const_iterator cbegin() {
      return const_iterator(native_string.cbegin());
    }    
    inline const_iterator cend() {
      return const_iterator(native_string.cend());
    }
    //@}

    //@{
    /**
     * Append from input iterators.
     *
     * Note that this is only possible from iterators of the same
     * encoding. This will not perform any conversion.
     */
    template <typename StorageType>
    inline basic_encodedstring& append
    (
     typename basic_encodedstring<Encoding, StorageType>::const_iterator first,
     typename basic_encodedstring<Encoding, StorageType>::const_iterator last
     ) {
      native_string.append
        (Encoding::template native_const_iterator<StorageType>(first),
         Encoding::template native_const_iterator<StorageType>(last)
         );
      return *this;
    }

    inline basic_encodedstring& append
    (const_iterator first,const_iterator last
     ) {
      return append<NativeString>(first,last);
    }

    template <typename StorageType>
    inline basic_encodedstring& append
    (basic_grapheme_iterator<basic_encodedstring<Encoding, StorageType>>& first,
     basic_grapheme_iterator<basic_encodedstring<Encoding, StorageType>>& last)
    {
      native_string.append((*first).codepoint_begin(),
                           (*last).codepoint_begin());
      return *this;
    }
    
    inline basic_encodedstring& append
    (basic_grapheme_iterator<basic_encodedstring>& first,
     basic_grapheme_iterator<basic_encodedstring>& last) {
      return append<NativeString>(first, last);
    }
    
    //@}

  };
    
}

#endif
