#ifndef INCLUDED_U5E_PROPS_GRAPHEME_CLUSTER_BREAK
#define INCLUDED_U5E_PROPS_GRAPHEME_CLUSTER_BREAK

#include <stdlib.h>
#include <u5e/codepoint.hpp>

namespace u5e {
  namespace props {
    class grapheme_cluster_break {
    public:
      enum prop_value_type {
	OTHER,
	PREPEND,
	CR,
	LF,
	CONTROL,
	EXTEND,
	REGIONAL_INDICATOR,
	SPACINGMARK,
	L,
	V,
	T,
	LV,
	LVT,
	E_BASE,
	E_MODIFIER,
	ZWJ,
	GLUE_AFTER_ZWJ,
	E_BASE_GAZ,
      };
      static prop_value_type resolve(codepoint c);
    };
  };
};

#endif
