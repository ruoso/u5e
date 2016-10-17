#ifndef INCLUDED_U5E_UTF8_BOUNDS
#define INCLUDED_U5E_UTF8_BOUNDS

#include <cmath>
#include <u5e/utf8_util.hpp>
#include <u5e/iterator_assertion.hpp>

namespace u5e {
  /**
   * \brief Check and enforce bounds of utf8 text
   *
   * This will only look at the last 6 octets of the text and will
   * only look at the first octet. It will not guarantee that the
   * entire text is valid. The intent of this class is to provide a
   * cheap safety check to make sure you will not have any under or
   * overflow when processing this text.
   *
   * \tparam WRAPPEDITERATOR The underlying type to be iterated over.
   */
  template <typename WRAPPEDITERATOR>
  class utf8_bounds {
  public:
    /**
     * The WRAPPEDITERATOR must match the attributes of char
     */
    iterator_assertion<WRAPPEDITERATOR, char> _assertions;

    /**
     * Check the bounds of the utf8 text, returns true if the text has
     * correct bounds.
     */
    static bool check(WRAPPEDITERATOR begin, WRAPPEDITERATOR end) {
      if (utf8_util::is_codepoint_continuation(*begin)) {
	return false;
      } else {
	int max_walkback = 6; // mathematically, it's impossible for
			      // something more than 6 elements away
			      // from the end to generate a overflow.
	int walkback = 0;
	while (walkback < max_walkback && end != begin) {
	  char octet = *end;
	  if (utf8_util::is_codepoint_start(octet)) {
	    if (utf8_util::codepoint_size(octet) > walkback) {
	      return false;
	    }
	  }
	  --end; walkback++;
	}
	return true;
      }
    }

    /**
     * Enforce the bounds of the utf8 text, replace any bad character
     * in the bounds by '?. Returns false if any substitution was made.
     */
    static bool enforce(WRAPPEDITERATOR begin, WRAPPEDITERATOR end) {
      bool ret = true;
      while (utf8_util::is_codepoint_continuation(*begin)) {
	*begin = '?';
	++begin;
	ret = false;
      }
      int max_walkback = 6; // mathematically, it's impossible for
			    // something more than 6 elements away
			    // from the end to generate a overflow.
      int walkback = 0;
      while (walkback < max_walkback && end != begin) {
	char octet = *end;
	if (utf8_util::is_codepoint_start(octet)) {
	  if (utf8_util::codepoint_size(octet) > walkback) {
	    *end = '?';
	    ret = false;
	  }
	}
	--end; walkback++;
      }
      return ret;
    }
  };
}

#endif
