#ifndef INCLUDED_U5E_COMPATIBILITY_AND_CANONICAL_DECOMPOSITION
#define INCLUDED_U5E_COMPATIBILITY_AND_CANONICAL_DECOMPOSITION

#include <iterator>
#include <algorithm>
#include <experimental/string_view>

#include <u5e/codepoint.hpp>
#include <u5e/props/compatibility_and_canonical_decomposition_mapping.hpp>
#include <u5e/utf32ne_string_view.hpp>

namespace u5e {

  /**
   * \brief Perform compatibility and canonical decomposition
   *
   * This is one step of the normalization process, you probably want
   * to use that instead.
   *
   * This is meant to be used as an operation for u5e::filter.
   * 
   * \tparam OutputStringType the output string type to be used.
   * Because this reads data from the database, the returned data is
   * utf32ne, so you need an OutputStringType that is compatible with
   * that.
   *
   */
  template <typename OutputStringType>
  inline int compatibility_and_canonical_decomposition
  (const codepoint input,
   OutputStringType& output) {
    return codepoint_decomposition
      ( input,
        output,
        props::compatibility_and_canonical_decomposition_mapping::resolve );
  }

}

#endif
