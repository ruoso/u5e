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
    typedef props::grapheme_cluster_break::prop_value_type g_c_b_vt;
    void find_end_of_grapheme() {
      // GB2
      if (end_of_grapheme_ == end_)
	return;
      // advance end_of_grapheme_ until it's no longer in the same grapheme

      // GB1
      // this always start as where_ == end_of_grapheme_;
      codepoint a = *end_of_grapheme_;
      end_of_grapheme_++;

      // TODO: actually implement the grapheme cluster support
      while (1) {
	// GB2
	if (end_of_grapheme_ == end_)
	  return;
	codepoint b = *end_of_grapheme_;

	g_c_b_vt va = props::grapheme_cluster_break::resolve(a);
	g_c_b_vt vb = props::grapheme_cluster_break::resolve(b);

	if (va == g_c_b_vt::CR &&
	    vb == g_c_b_vt::LF) {
	  // GB3
	} else if (va == g_c_b_vt::CR ||
		   va == g_c_b_vt::LF ||
		   va == g_c_b_vt::CONTROL) {
	  // GB4
	  return;
	} else if (vb == g_c_b_vt::CR ||
		   vb == g_c_b_vt::LF ||
		   vb == g_c_b_vt::CONTROL) {
	  // GB5
	  return;
	} else if (va == g_c_b_vt::L &&
		   (vb == g_c_b_vt::L ||
		    vb == g_c_b_vt::V ||
		    vb == g_c_b_vt::LV ||
		    vb == g_c_b_vt::LVT)) {
	  // GB6
	} else if ((va == g_c_b_vt::LV ||
		    va == g_c_b_vt::V) &&
		   (vb == g_c_b_vt::V ||
		    vb == g_c_b_vt::T)) {
	  // GB7
	} else if ((va == g_c_b_vt::LVT ||
		    va == g_c_b_vt::T) &&
		   vb == g_c_b_vt::T) {
	  // GB8
	} else if (vb == g_c_b_vt::EXTEND ||
		   vb == g_c_b_vt::ZWJ) {
	  // GB9
	} else if (vb == g_c_b_vt::SPACINGMARK) {
	  // GB9a
	} else if (va == g_c_b_vt::PREPEND) {
	  // GB9b
	} else if ( ( (va == g_c_b_vt::E_BASE ||
		       va == g_c_b_vt::E_BASE_GAZ) &&
		      vb == g_c_b_vt::E_MODIFIER) ||
		    ( va == g_c_b_vt::EXTEND &&
		      vb == g_c_b_vt::E_MODIFIER )) {
	  // GB10 -- that is the interpretation I can make
	  // of the combination of the fact that you should be able
	  // to compare only two adjancent characters and the text of
	  // the standard.
	} else if (va == g_c_b_vt::ZWJ &&
		   (vb == g_c_b_vt::GLUE_AFTER_ZWJ ||
		    vb == g_c_b_vt::E_BASE_GAZ)) {
	  // GB11
	} else if (va == g_c_b_vt::REGIONAL_INDICATOR &&
		   vb == g_c_b_vt::REGIONAL_INDICATOR) {
	  // GB12, GB13
	  // again, I take the liberty to assume the earlier part of the text
	  // that says you only need to look at two adjacent characters
	} else {
	  // GB999
	  return;
	}
	
	a = b;
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
