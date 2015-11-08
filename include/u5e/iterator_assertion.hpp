#ifndef INCLUDED_U5E_ITERATOR_ASSERTION
#define INCLUDED_U5E_ITERATOR_ASSERTION

namespace u5e {
  template <typename TRAIT, typename T>
  class iterator_assertion {
    static_assert(sizeof(typename TRAIT::value_type)==sizeof(T),
                  "sizeof value_type incompatible with encoding");
    static_assert(alignof(typename TRAIT::value_type)==alignof(T),
                  "alignof value_type incompatible with encoding");
    static_assert(std::is_integral<typename TRAIT::value_type>::value,
                  "value_type is not an integral type");
  };
};

#endif
