#ifndef INCLUDED_U5E_ITERATOR_ASSERTION
#define INCLUDED_U5E_ITERATOR_ASSERTION

namespace u5e {

  // template for static asserts, no assertions by default
  template <typename WRAPPEDITERATOR, typename T, bool ISCLASS, bool ISPOINTER>
  class iterator_assertion {
  };

  template <typename WRAPPEDITERATOR, typename T>
  class iterator_assertion<WRAPPEDITERATOR, T, true, false> {
    typedef typename WRAPPEDITERATOR::value_type vt;
    static_assert(sizeof(vt)==sizeof(T),
                  "sizeof WRAPPEDITERATOR::value_type incompatible with utf8");
    static_assert(alignof(vt)==alignof(T),
                  "alignof WRAPPEDITERATOR::value_type incompatible with utf8");
    static_assert(std::is_integral<vt>::value,
                  "WRAPPEDITERATOR::value_type is not an integral type");
  };

  template <typename WRAPPEDITERATOR, typename T>
  class iterator_assertion<WRAPPEDITERATOR, T, false, true> {
    typedef typename std::remove_pointer<WRAPPEDITERATOR>::type vt;
    static_assert(sizeof(vt)==sizeof(T),
                  "sizeof *WRAPPEDITERATOR incompatible with utf8");
    static_assert(alignof(vt)==alignof(T),
                  "alignof *WRAPPEDITERATOR incompatible with utf8");
    static_assert(std::is_integral<vt>::value,
                  "*WRAPPEDITERATOR is not an integral type");
  };

  template <typename WRAPPEDITERATOR, typename T>
  class iterator_assertion<WRAPPEDITERATOR, T, false, false> {
    static_assert(std::is_class<WRAPPEDITERATOR>::value,
                  "WRAPPEDITERATOR must be either a class or a pointer");
  };


};

#endif
