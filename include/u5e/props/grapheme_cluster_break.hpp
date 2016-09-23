#ifndef INCLUDED_U5E_PROPS_GRAPHEME_CLUSTER_BREAK
#define INCLUDED_U5E_PROPS_GRAPHEME_CLUSTER_BREAK

#include <u5e/codepoint.hpp>

namespace u5e {
  namespace props {
    class grapheme_cluster_break {
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
      typedef struct range_data_st {
	codepoint range_start;
	codepoint range_end;
	prop_value_type value;
      } range_data;
      static constexpr range_data ranges[] = {
	// this file is generated from the unicode database
	// grapheme_cluster_break is small enough that it makes sense
	// to just load it
        #include "grapheme_cluster_break_data.hpp"
      };
      static constexpr prop_value_type resolve(codepoint c) {
	// 
      };
    };
  };
};

#endif
