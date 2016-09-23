#ifndef INCLUDED_U5E_PROPS_GRAPHEME_CLUSTER_BREAK
#define INCLUDED_U5E_PROPS_GRAPHEME_CLUSTER_BREAK

#include <u5e/codepoint.hpp>

namespace u5e {
  namespace props {
    class grapheme_cluster_break {
      enum value {
	OTHER,
	PREPEND,
	CR,
	LF,
	CONTROL,
	EXTEND,
	REGIONAL_INDICATOR,
	SPACING_MARK,
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
      static constexpr value resolve(codepoint c) {
	static constexpr ranges = {
	  // this file is generated from the unicode database
	  // grapheme_cluster_base is small enough that it makes sense
	  // to just load it
          #include "grapheme_cluster_break_data.hpp"
	};
      };
    };
  };
};

#endif
