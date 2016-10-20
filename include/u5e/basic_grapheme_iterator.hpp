#ifndef INCLUDED_U5E_BASIC_GRAPHEME_ITERATOR
#define INCLUDED_U5E_BASIC_GRAPHEME_ITERATOR

#include <u5e/basic_grapheme.hpp>
#include <u5e/props/grapheme_cluster_break.hpp>

namespace u5e {

  /**
   * \brief Iterator that describes full graphemes.
   *
   * \tparam UnderlyingEncodedStringView the underlying encoded string
   * type with an underlying native string-like type.
   */
  template <typename UnderlyingEncodedStringView>
  class basic_grapheme_iterator {
  public:
    /**
     * The type of the underlying encoded iterator
     */
    typedef typename UnderlyingEncodedStringView::const_iterator
    const_codepoint_iterator;

    /**
     * the specific grapheme type for this encoded string view
     */
    typedef basic_grapheme<UnderlyingEncodedStringView> grapheme;
    
    //@{
    /**
     * The begin and end iterators for the whole text are necessary for
     * bounds check, since the size of graphemes cannot be predicted.
     */
    const_codepoint_iterator begin_;
    const_codepoint_iterator end_;
    //@}
    //@{
    /**
     * This par of iterators point to where we are now and where the end
     * of the current grapheme is.
     */
    const_codepoint_iterator where_;
    const_codepoint_iterator end_of_grapheme_;
    //@}

    typedef props::grapheme_cluster_break::prop_value_type g_c_b_vt;

    /**
     * The unicode standard documents that a grapheme boundary can be
     * determined by looking just at two adjecent codepoints.
     */
    bool is_grapheme_boundary(codepoint a, codepoint b) {
      g_c_b_vt va = props::grapheme_cluster_break::resolve(a);
      g_c_b_vt vb = props::grapheme_cluster_break::resolve(b);

      if (va == g_c_b_vt::CR &&
	  vb == g_c_b_vt::LF) {
	// GB3
	return false;
      } else if (va == g_c_b_vt::CR ||
		 va == g_c_b_vt::LF ||
		 va == g_c_b_vt::CONTROL) {
	// GB4
	return true;
      } else if (vb == g_c_b_vt::CR ||
		 vb == g_c_b_vt::LF ||
		 vb == g_c_b_vt::CONTROL) {
	// GB5
	return true;
      } else if (va == g_c_b_vt::L &&
		 (vb == g_c_b_vt::L ||
		  vb == g_c_b_vt::V ||
		  vb == g_c_b_vt::LV ||
		  vb == g_c_b_vt::LVT)) {
	// GB6
	return false;
      } else if ((va == g_c_b_vt::LV ||
		  va == g_c_b_vt::V) &&
		 (vb == g_c_b_vt::V ||
		  vb == g_c_b_vt::T)) {
	// GB7
	return false;
      } else if ((va == g_c_b_vt::LVT ||
		  va == g_c_b_vt::T) &&
		 vb == g_c_b_vt::T) {
	// GB8
	return false;
      } else if (vb == g_c_b_vt::EXTEND ||
		 vb == g_c_b_vt::ZWJ) {
	// GB9
	return false;
      } else if (vb == g_c_b_vt::SPACINGMARK) {
	// GB9a
	return false;
      } else if (va == g_c_b_vt::PREPEND) {
	// GB9b
	return false;
      } else if ( ( (va == g_c_b_vt::E_BASE ||
		     va == g_c_b_vt::E_BASE_GAZ) &&
		    vb == g_c_b_vt::E_MODIFIER) ||
		  ( va == g_c_b_vt::EXTEND &&
		    vb == g_c_b_vt::E_MODIFIER )) {
	// GB10 -- that is the interpretation I can make
	// of the combination of the fact that you should be able
	// to compare only two adjancent characters and the text of
	// the standard.
	return false;
      } else if (va == g_c_b_vt::ZWJ &&
		 (vb == g_c_b_vt::GLUE_AFTER_ZWJ ||
		  vb == g_c_b_vt::E_BASE_GAZ)) {
	// GB11
	return false;
      } else if (va == g_c_b_vt::REGIONAL_INDICATOR &&
		 vb == g_c_b_vt::REGIONAL_INDICATOR) {
	// GB12, GB13
	// again, I take the liberty to assume the earlier part of the text
	// that says you only need to look at two adjacent characters
	return false;
      } else {
	// GB999
	return true;
      }
    }
    
    //@{
    /**
     * Use the data from the unicode database to find the start and
     * end of the current grapheme.
     */
    void find_end_of_grapheme() {
      // GB2
      if (end_of_grapheme_ == end_)
	return;
      // advance end_of_grapheme_ until it's no longer in the same grapheme

      // GB1
      // this always start as where_ == end_of_grapheme_;
      codepoint a = *end_of_grapheme_;
      end_of_grapheme_++;

      while (1) {
	// GB2
	if (end_of_grapheme_ == end_)
	  return;
	codepoint b = *end_of_grapheme_;

	if (is_grapheme_boundary(a, b)) {
	  return;
	}

	a = b;
	end_of_grapheme_++;
      }
    }

    void find_start_of_grapheme() {
      // GB2
      if (where_ == begin_)
	return;
      // rewind where_ until it's no longer in the same grapheme

      // GB1
      // this always start as copy = where_
      const_codepoint_iterator copy = where_;
      --copy;
      codepoint a = *copy;

      while (1) {
	if (where_ == begin_)
	  return;
	codepoint b = *where_;

	if (is_grapheme_boundary(a, b)) {
	  return;
	}

	a = b;
	--where_;
      }
    }
    //@}

    /**
     * \brief start at the beginning of the text
     */
    basic_grapheme_iterator(const_codepoint_iterator b,
			    const_codepoint_iterator e)
      :begin_(b), end_(e), where_(b), end_of_grapheme_(b) {
      find_end_of_grapheme();
    };

    /**
     * \brief start at a specific point
     * find the start and the end of the grapheme
     */
    basic_grapheme_iterator(const_codepoint_iterator b,
			    const_codepoint_iterator e,
			    const_codepoint_iterator w)
      :begin_(b), end_(e), where_(w), end_of_grapheme_(w) {
      find_start_of_grapheme();
      find_end_of_grapheme();
    };

    /**
     * \brief start at a specific point - precalculated
     * start and end of grapheme
     */
    basic_grapheme_iterator(const_codepoint_iterator b,
			    const_codepoint_iterator e,
			    const_codepoint_iterator w,
			    const_codepoint_iterator we)
      :begin_(b), end_(e), where_(w), end_of_grapheme_(we) {
    };

    /**
     * \brief copy constructor
     */
    basic_grapheme_iterator(const basic_grapheme_iterator& copy)
      :begin_(copy.begin_), end_(copy.end_),
       where_(copy.where_), end_of_grapheme_(copy.end_of_grapheme_) {}
    
    /**
     * dereference to a grapheme object
     */
    grapheme operator*() {
      return grapheme(where_, end_of_grapheme_);
    }

    //@{
    /**
     * advance one grapheme
     */
    basic_grapheme_iterator operator++() {
      where_ = end_of_grapheme_;
      find_end_of_grapheme();
      return *this;
    }

    basic_grapheme_iterator operator++(int i) {
      basic_grapheme_iterator copy(*this);
      ++(*this);
      return copy;
    }
    //@}

    /**
     * delegate the comparison to the underlying iterator
     */
    bool operator==(const_codepoint_iterator other) {
      if (where_ == other) {
	return true;
      } else {
	for (const_codepoint_iterator copy = where_;
	     copy != end_of_grapheme_; copy++) {
	  if (copy == other) {
	    return true;
	  }
	}
	return false;
      }
    }

    /**
     * delegate the comparison to the underlying iterator
     */
    bool operator==(basic_grapheme_iterator other) {
      for (const_codepoint_iterator copy = where_;
	   copy != end_of_grapheme_; copy++) {
	if (other == copy) {
	  return true;
	}
      }
      return false;
    }

    /**
     * delegate the comparison to the underlying iterator
     */
    bool operator!=(basic_grapheme_iterator other) {
      return !(*this == other);
    }

    /**
     * delegate the comparison to the underlying iterator
     */
    bool operator!=(const_codepoint_iterator other)
    {
      return !(*this == other);
    }
  };
};

#endif
