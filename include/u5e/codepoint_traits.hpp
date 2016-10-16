#ifndef INCLUDED_U5E_CODEPOINT_TRAITS
#define INCLUDED_U5E_CODEPOINT_TRAITS

#include <inttypes.h>

namespace u5e {
  /**
   * \brief Type information for codepoint
   *
   * This class exists only to provide an interface similar to that of
   * the stream and string types. But it is not truly parameterizable,
   * since a codepoint always means the same thing.
   */
  class codepoint_traits {
  public:
    //@{
    /**
     * Basic meta-description of a codepoint
     */
    typedef int32_t    int_type;
    typedef uint32_t   pos_type;
    typedef int32_t    off_type;
    //@}
  };
}

#endif
