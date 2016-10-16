#ifndef INCLUDED_U5E_ENCODING_ASSERTION
#define INCLUDED_U5E_ENCODING_ASSERTION

#include <iterator>
#include <u5e/iterator_assertion.hpp>

namespace u5e {
  /**
   * \brief Assert the encoding matches the underlying type
   *
   * Tests that the encoding can be used with the specific
   * underlying string type.
   */
  template <typename BUFFERTYPE, typename T>
  class encoding_assertion {
    iterator_assertion<typename BUFFERTYPE::iterator, T>
    _assertion1;
    iterator_assertion<typename BUFFERTYPE::const_iterator, T>
    _assertion2;
    iterator_assertion<typename BUFFERTYPE::reverse_iterator, T>
    _assertion3;
    iterator_assertion<typename BUFFERTYPE::const_reverse_iterator, T>
    _assertion4;
  };
}

#endif
