#ifndef INCLUDED_U5E_UTF8_BOUNDS
#define INCLUDED_U5E_UTF8_BOUNDS

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
      return false;
    }

    /**
     * Enforce the bounds of the utf8 text, replace any bad character
     * in the bounds by '?. Returns false if any substitution was made.
     */
    static bool enforce(WRAPPEDITERATOR begin, WRAPPEDITERATOR end) {
      return false;
    }
  };
}

#endif
