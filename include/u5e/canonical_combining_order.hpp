#ifndef INCLUDED_U5E_CANONICAL_COMBINING_ORDER
#define INCLUDED_U5E_CANONICAL_COMBINING_ORDER

#include <u5e/props/canonical_combining_class.hpp>

namespace u5e {

  /**
   * \brief compare codepoints according to the canonical combining order
   *
   * This is intended to be used with std::sort on a utf32ne string type.
   */
  inline bool canonical_combining_order(int a, int b) {
    return
      props::canonical_combining_class::resolve(a)
      <
      props::canonical_combining_class::resolve(b);
  }
}

#endif
