#include <u5e/props/canonical_decomposition_mapping.hpp>
#include <initializer_list>
#include <iterator>
#include <cstdint>

typedef const std::initializer_list<const std::initializer_list<const int>>
data_t;

static data_t 
data =
  {
#include "canonical_decomposition_mapping_data.hpp"
  };

static int compare_value_to_row(const void* pkey,
                                const void* pelem) {
  int const * const key = (int const * const)pkey;
  int const * const * const ref = (int const * const * const)pelem;
  int const * const elem = *ref;
  if (key[0] < elem[0]) {
    return -1;
  } else if (key[0] > elem[0]) {
    return 1;
  } else {
    return 0;
  }
};

namespace u5e {
  namespace props {
    int const * const canonical_decomposition_mapping::resolve(int input) {
      int const * const * elem =
        (int const * const * const)
        bsearch((const void*)&input, (const void*)data.begin(),
                data.size(), sizeof(data_t::value_type),
                compare_value_to_row);
      if (elem == NULL) {
        return NULL;
      } else {
        int const * it = *elem;
        it++; // first element in array is codepoint itself
        return it;
      }
    }
  }
}

