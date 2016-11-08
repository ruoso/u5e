#include <u5e/props/canonical_composition_mapping.hpp>
#include <initializer_list>
#include <iterator>
#include <cstdint>

typedef const std::initializer_list<const std::initializer_list<const int>>
data_t;

static data_t 
data =
  {
#include "canonical_composition_mapping_data.hpp"
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
    if (key[1] < elem[1]) {
      return -1;
    } else if (key[1] > elem[1]) {
      return 1;
    } else {
      return 0;
    }
  }
};

namespace u5e {
  namespace props {
    bool canonical_composition_mapping::resolve(int a, int b, int* r_composed) {
      int input[3] = { a, b, 0 };
      int const * const * elem =
        (int const * const * const)
        bsearch((const void*)&input, (const void*)data.begin(),
                data.size(), sizeof(data_t::value_type),
                compare_value_to_row);
      if (elem == NULL) {
        return false;
      } else {
        int const * it = *elem;
        *r_composed = it[2];
        return true;
      }
    }
  }
}

