#ifndef INCLUDED_U5E_GRAPHEME_ITERATOR
#define INCLUDED_U5E_GRAPHEME_ITERATOR

#include <u5e/basic_grapheme.hpp>

namespace u5e {

  /**
   * u5e::grapheme_iterator
   *
   * This class offer an iterator that describes full graphemes.
   */
  template <typename UnderlyingEncodedStringView>
  class grapheme_iterator {
  public:
    typedef typename UnderlyingEncodedStringView::const_iterator
    const_codepoint_iterator;

    typedef basic_grapheme<UnderlyingEncodedStringView> grapheme;
    
  protected:
    const_codepoint_iterator begin_;
    const_codepoint_iterator end_;
    const_codepoint_iterator where_;
    
  public:
    /**
     * the specific grapheme type for this encoded string view
     */
    grapheme_iterator(const_codepoint_iterator b, const_codepoint_iterator e)
      :begin_(b), end_(e), where_(b) {};

    grapheme operator*() {
      return grapheme(where_, where_);
    }

    grapheme_iterator operator++() {
      return *this;
    }

    grapheme_iterator operator++(int i) {
      return *this;
    }

    bool operator==(const_codepoint_iterator other) {
      return where_ == other;
    }
};

};

#endif
