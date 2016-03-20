#ifndef INCLUDED_U5E_CODEPOINT_TRAITS
#define INCLUDED_U5E_CODEPOINT_TRAITS

#include <inttypes.h>

namespace u5e {
  /**
   * u5e::codepoint_traits
   *
   * This class exists only to provide an interface similar to that of
   * the stream and string types. But it is not truly parameterizable,
   * since a codepoint always means the same thing.
   */
  class codepoint_traits {
  public:
    typedef int32_t    int_type;
    typedef uint32_t   pos_type;
    typedef int32_t    off_type;
  };
}

#endif
