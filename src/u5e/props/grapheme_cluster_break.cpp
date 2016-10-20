
#include <u5e/props/grapheme_cluster_break.hpp>

using u5e::codepoint;
using u5e::props::grapheme_cluster_break;

typedef struct range_data_st {
  codepoint range_start;
  codepoint range_end;
  grapheme_cluster_break::prop_value_type value;
} range_data;

static range_data ranges[] = {
  // this file is generated from the unicode database
  // grapheme_cluster_break is small enough that it makes sense
  // to just load it
#include "grapheme_cluster_break_data.hpp"
};

static int compare_value_to_range(const void* pkey,
                                  const void* pelem) {
  range_data* key = (range_data*)pkey;
  range_data* elem = (range_data*)pelem;
  if (key->range_start < elem->range_start) {
    return -1;
  } else if (key->range_start >= elem->range_start &&
             key->range_start <= elem->range_end) {
    return 0;
  } else {
    return 1;
  }
};

template <typename T, size_t N>
static constexpr size_t countof(T(&)[N])
{
  return N;
}

grapheme_cluster_break::prop_value_type
grapheme_cluster_break::resolve(codepoint c) {
  range_data key = {c, c, prop_value_type::OTHER};
  range_data* elem = (range_data*)
    bsearch(&key, ranges,
            countof(ranges), sizeof(range_data),
            compare_value_to_range);
  if (elem) {
    return elem->value;
  } else {
    return grapheme_cluster_break::prop_value_type::OTHER;
  }
};

