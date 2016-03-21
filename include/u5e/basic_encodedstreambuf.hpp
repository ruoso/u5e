#ifndef INCLUDED_U5E_BASIC_ENCODEDSTREAMBUF
#define INCLUDED_U5E_BASIC_ENCODEDSTREAMBUF

#include <u5e/codepoint.hpp>
#include <ios>

namespace u5e {
  
  /**
   * u5e::basic_encodedstreambuf is the encoding-aware basic_streambuf
   * alternative. This provides the type-safety on the handling of
   * encoded strings, its type include in its definition:
   *
   * This streambuf represents the encoding, and it will always ensure
   * you read and write complete characters to/from the underlying
   * streambuf.
   *
   * This class still does not handle higher-level concepts, such as
   * normalization and language support, it deals exclusively with
   * encodings.
   *
   * * Encoding: Text is always represented in a specific encoding,
   *   there is no such thing as a "natural", or "native"
   *   representation of text, for that reason, the encoding is a part
   *   of the type.
   *
   * * UnderlyingStreamBuf: In order to re-use the IO support already
   *   implemented by C++ streams, this will always be implemented as
   *   a wrapper around an underlying stream buf. The idea is that the
   *   C++ streams and string libraries operate on unencoded memory,
   *   while the u5e types offer a layer on top of that for the
   *   purposes of implementing unicode in a type-safe way.
   *
   */
  template <typename Encoding,
            typename UnderlyingStreamBuf>
  class basic_encodedstreambuf {
  public:
    /**
     * We make a few local typedefs to simplify.
     */
    typedef typename UnderlyingStreamBuf::char_type underlying_char_type;
    typedef typename Encoding::encoded_unit encoding_char_type;

    /**
     * We offer a similar interface to that of streambuf.
     */
    typedef codepoint                  char_type;
    typedef codepoint_traits           traits_type;
    typedef codepoint_traits::int_type int_type;
    typedef codepoint_traits::pos_type pos_type;
    typedef codepoint_traits::off_type off_type;
    
    /**
     * We need to statically assert that the underlying char type
     * matches the expectations of the encoding.
     *
     * While streambuf has a char_type member, the encoding has a
     * encoded_unit member. They must have the same size and
     * alignment, otherwise this can't work.
     *
     * This is important, because the Encoding needs to know how may
     * bytes it will get at a time and how an array of such type will
     * behave.
     */
    static_assert(sizeof(underlying_char_type) ==
                  sizeof(encoding_char_type),
                  "sizeof char_type incompatible with encoding");
    static_assert(alignof(underlying_char_type) ==
                  alignof(encoding_char_type),
                  "alignof value_type incompatible with encoding");

    /**
     * Simple sanity check.
     */
    static_assert(std::is_integral<encoding_char_type>::value,
                  "encoding char type is not an integral type");
    static_assert(std::is_integral<underlying_char_type>::value,
                  "underlying char type is not an integral type");

    basic_encodedstreambuf(UnderlyingStreamBuf& in) :underlying_streambuf(in) {}

    /**
     * A basic_encodedstreambuf is always implemented as a wrapper of
     * some other streambuf. This is a public member so the user can
     * freely operate on it.
     */
    UnderlyingStreamBuf& underlying_streambuf;
    
    /**
     * # Locales
     *
     * In basic_streambuf, locale is used for identifying when code
     * conversions need to be made. Since the point of this is to make
     * the encoding more explicit into the type itself, there is no
     * need for locale to be insert in this level.
     */

    /**
     * # Positioning
     */

    /**
     * pubsetbuf
     *
     * Wraps pubsetbuf in the underlying streambuf.
     */
    basic_encodedstreambuf<Encoding, UnderlyingStreamBuf>
    pubsetbuf(underlying_char_type* s, std::streamsize n) {
      underlying_streambuf = underlying_streambuf.pubsetbuf(s, n);
      return *this;
    }

    /**
     * pubseekoff
     *
     * Seeks to the given offset from a given base.
     *
     * Note that if the encoding doesn't have fixed size codepoint,
     * this may be a potentially expensive operation.
     *
     * OTOH, you may choose to do a pubseekoff on the underlying
     * streambuf, and only then so a single codepoint pubseekoff on
     * the encodedstreambuff in order to get to the correct code
     * border.
     *
     * Since returning the absolute position would be unecessarily
     * expensive, this will not actually return any value.
     *
     * This method is entirely delegated to the encoding.
     */
    void pubseekoff( off_type off, std::ios_base::seekdir dir,
                     std::ios_base::openmode which = std::ios_base::in | std::ios_base::out) {
      Encoding::streambuf_pubseekoff(underlying_streambuf, off, dir, which);
    }
    
    /**
     * pubseekpos
     *
     * pubseekpos is potentially very expensive, since it may be
     * required to traverse the entire stream, in case the encoding is
     * not fixed-sized.
     *
     * This method is entirely delegated to the encoding.
     */
    void pubseekpos( pos_type pos,
                     std::ios_base::openmode which = std::ios_base::in | std::ios_base::out) {
      Encoding::streambuf_pubseekpos(underlying_streambuf, pos, which);
    }

    /**
     * pubsync
     *
     * Delegated to the underlying streambuf
     */
    int pubsync() {
      return underlying_streambuf.pubsync();
    }

    /**
     * # Get Area
     */

    /**
     * in_avail
     *
     * Returns how many *complete* codepoints are the get area.
     *
     * This method is entirely delegated to the encoding.
     */
    std::streamsize in_avail() {
      return Encoding::streambuf_in_avail(underlying_streambuf);
    }
    
    /**
     * snextc
     * 
     * Again, only reads *complete* codepoints, may get more
     * characters in order to complete it.
     *
     * This method is entirely delegated to the encoding.     
     */
    int_type snextc() {
      return Encoding::streambuf_snextc(underlying_streambuf);
    }

    /**
     * sbumpc
     * 
     * Again, only reads *complete* codepoints.
     *
     * This method is entirely delegated to the encoding.     
     */
    int_type sbumpc() {
      return Encoding::streambuf_sbumpc(underlying_streambuf);
    }

    /**
     * sgetc
     * 
     * Again, only reads *complete* codepoints.
     *
     * This method is entirely delegated to the encoding.     
     */
    int_type sgetc() {
      return Encoding::streambuf_sgetc(underlying_streambuf);
    }

    /**
     * sgetn
     * 
     * Again, only reads *complete* codepoints.
     *
     * Populates an array of codepoints. You may want to look at
     * sgetn_encoded instead.
     *
     * This method is entirely delegated to the encoding.     
     */
    std::streamsize sgetn(codepoint* s, std::streamsize count) {
      return Encoding::streambuf_sgetn(underlying_streambuf, s, count);
    }

    /**
     * sgetn_encoded
     *
     * The difference between sgetn and sgetn_encoded is that it
     * allows a simple copy of the data if they are both on the same
     * encoding, instead of parsing the entire sequence.
     *
     * Note that encoded_count as well as the return size here refers
     * to the size of the buffer in the encoded char type, not the
     * count of codepoints.
     *
     * The additional parameter allows obtaining how many codepoints
     * were read in the process.
     *
     * But it will only populate complete characters.
     *
     * This method is entirely delegated to the encoding.
     */
    std::streamsize sgetn_encoded(encoding_char_type* s,
                                  std::streamsize encoded_count,
                                  std::streamsize* codepoint_count_ret) {
      return Encoding::streambuf_sgetn(underlying_streambuf, s, encoded_count,
                                       codepoint_count_ret);
    }

    /**
     * # Put Area
     */

    /**
     * sputc
     *
     * Writes a complete codepoint or return overflow.
     *
     * This method is entirely delegated to the encoding.
     */
    int_type sputc(codepoint c) {
      return Encoding::streambuf_sputc(underlying_streambuf, c);
    }

    /**
     * sputn
     *
     * Writes from an array of codepoints. You may want to look at
     * sputn_encoded instead.
     *
     * Writes only complete codepoints.
     *
     * This method is entirely delegated to the encoding.
     */
    std::streamsize sputn(codepoint* s, std::streamsize count) {
      return Encoding::streambuf_sputn(underlying_streambuf, s, count);
    }
    
    /**
     * sputn_encoded
     *
     * The difference of this method is that no encoding conversion is
     * necessary, and a straight read and write can be performed.
     *
     * The count and return value represent the count in the unit of
     * the encoding, not on codepoints.
     *
     * The additional parameter allows obtaining how many codepoints
     * were written in the process.
     *
     * But even still, writes only complete codepoints.
     *
     * This method is entirely delegated to the encoding.
     */
    std::streamsize sputn_encoded(encoding_char_type* s,
                                  std::streamsize count,
                                  std::streamsize* codepoint_count_r) {
      return Encoding::streambuf_sputn_encoded(underlying_streambuf, s, count,
                                               codepoint_count_r);
    }

    /**
     * # PutBack
     */

    /**
     * sputbackc
     *
     * This method is entirely delegated to the encoding.
     */
    int_type sputbackc( codepoint c ) {
      return Encoding::streambuf_sputbackc(underlying_streambuf, c);
    }
    
    /**
     * sungetc
     *
     * This method is entirely delegated to the encoding.
     */
    int_type sungetc() {
      return Encoding::streambuf_sungetc(underlying_streambuf);
    }
  };
};

#endif

