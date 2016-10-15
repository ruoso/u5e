#ifndef INCLUDED_U5E_ITERATOR_ASSERTION
#define INCLUDED_U5E_ITERATOR_ASSERTION

#include <iterator>

namespace u5e {
  /**
   * asserts that the iterator is consistently defined
   */
  template <typename WRAPPED, typename T>
  class iterator_assertion {
    typedef typename std::iterator_traits<WRAPPED>::value_type VT;
    static_assert(sizeof(VT)==sizeof(T),
                  "sizeof value_type incompatible with encoding");
    static_assert(alignof(VT)==alignof(T),
                  "alignof value_type incompatible with encoding");
    static_assert(std::is_integral<VT>::value,
                  "value_type is not an integral type");
  };
};

#endif
