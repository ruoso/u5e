#ifndef INCLUDED_U5E_ENCODING_ASSERTION
#define INCLUDED_U5E_ENCODING_ASSERTION

namespace u5e {

  // template for static asserts, no assertions by default
  template <typename BUFFERTYPE, typename T, bool ISCLASS>
  class encoding_assertion {
  };

  template <typename BUFFERTYPE, typename T>
  class encoding_assertion<BUFFERTYPE, T, true> {
    typedef typename BUFFERTYPE::value_type vt;
    static_assert(sizeof(vt)==sizeof(T),
                  "sizeof BUFFERTYPE::value_type incompatible with utf8");
    static_assert(alignof(vt)==alignof(T),
                  "alignof BUFFERTYPE::value_type incompatible with utf8");
    static_assert(std::is_integral<vt>::value,
                  "BUFFERTYPE::value_type is not an integral type");
  };

  template <typename BUFFERTYPE, typename T>
  class encoding_assertion<BUFFERTYPE, T, false> {
    static_assert(std::is_class<BUFFERTYPE>::value,
                  "BUFFERTYPE must be a class");
  };


};

#endif
