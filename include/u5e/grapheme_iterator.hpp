#ifndef INCLUDED_U5E_GRAPHEME_ITERATOR
#define INCLUDED_U5E_GRAPHEME_ITERATOR

#include <u5e/basic_grapheme.hpp>
#include <u5e/props/grapheme_cluster_break.hpp>

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

    /**
     * the specific grapheme type for this encoded string view
     */
    typedef basic_grapheme<UnderlyingEncodedStringView> grapheme;
    
  protected:
    // we need begin_ and end_ for bounds check
    const_codepoint_iterator begin_;
    const_codepoint_iterator end_;
    // where we actually are...
    const_codepoint_iterator where_;
    const_codepoint_iterator end_of_grapheme_;

  private:
    void find_end_of_grapheme() {
      if (end_of_grapheme_ == end_)
	return;
      // advance end_of_grapheme_ until it's no longer in the same grapheme
      // this always start as where_ == end_of_grapheme_;
      end_of_grapheme_++;

      // TODO: actually implement the grapheme cluster support
      while (1) {
	if (end_of_grapheme_ == end_)
	  return;

	
	
	end_of_grapheme_++;
      }
    }
    
  public:
    grapheme_iterator(const_codepoint_iterator b,
		      const_codepoint_iterator e)
      :begin_(b), end_(e), where_(b), end_of_grapheme_(b) {
      find_end_of_grapheme();
    };

    grapheme_iterator(const_codepoint_iterator b,
		      const_codepoint_iterator e,
		      const_codepoint_iterator w)
      :begin_(b), end_(e), where_(w), end_of_grapheme_(w) {
      find_end_of_grapheme();
    };

    grapheme_iterator(const_codepoint_iterator b,
		      const_codepoint_iterator e,
		      const_codepoint_iterator w,
		      const_codepoint_iterator we)
      :begin_(b), end_(e), where_(w), end_of_grapheme_(we) {
    };

    grapheme_iterator(const grapheme_iterator& copy)
      :begin_(copy.begin_), end_(copy.end_),
       where_(copy.where_), end_of_grapheme_(copy.end_of_grapheme_) {}
    
    grapheme operator*() {
      return grapheme(where_, end_of_grapheme_);
    }

    grapheme_iterator operator++() {
      where_ = end_of_grapheme_;
      find_end_of_grapheme();
      return *this;
    }

    grapheme_iterator operator++(int i) {
      grapheme_iterator copy(*this);
      ++(*this);
      return copy;
    }

    bool operator==(const_codepoint_iterator other) {
      return where_ == other;
    }
};

};

#endif
