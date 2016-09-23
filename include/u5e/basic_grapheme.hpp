#ifndef INCLUDED_U5E_BASIC_GRAPHEME
#define INCLUDED_U5E_BASIC_GRAPHEME

namespace u5e {
  /**
   * u5e::basic_grapheme
   *
   * Represents a single grapheme cluster. It works by holding start
   * and end values for an underlying encodedstring_view-like object.
   */
  template <typename UnderlyingEncodedStringView>
  class basic_grapheme {
  public:
    /**
     * codepoint_iterator allows you to traverse the codepoints inside
     * this grapheme.
     */
    typedef typename UnderlyingEncodedStringView::const_iterator
    const_codepoint_iterator;

  private:
    /**
     * represents where the grapheme starts
     */
    const_codepoint_iterator d_begin;
    
    /**
     * represents where the grapheme ends
     */
    const_codepoint_iterator d_end;

  public:
    /**
     * Simple constructor
     */
    basic_grapheme() {};
    
    basic_grapheme(const_codepoint_iterator b,
			   const_codepoint_iterator e)
      :d_begin(b), d_end(e) {};

    /**
     * get the beginning of the codepoints
     */
    const_codepoint_iterator codepoint_begin() {
      return d_begin;
    }

    /**
     * get the end of the codepoints
     */
    const_codepoint_iterator codepoint_end() {
      return d_end;
    }
  };
}

#endif
