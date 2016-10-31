#ifndef INCLUDED_U5E_CANONICAL_DECOMPOSITION
#define INCLUDED_U5E_CANONICAL_DECOMPOSITION

#include <iterator>
#include <algorithm>
#include <experimental/string_view>

#include <u5e/codepoint.hpp>
#include <u5e/props/canonical_decomposition_mapping.hpp>
#include <u5e/utf32ne_string_view.hpp>

namespace u5e {

  /**
   * \brief Perform codepoint-by-codepoint canonical decomposition
   *
   * This is one step of the normalization process, you probably want
   * to use that instead.
   *
   * This is meant to be used as an operation for u5e::filter.
   *
   * 
   * \tparam OutputStringType the output string type to be used.
   * Because this reads data from the database, the returned data is
   * utf32ne, so you need an OutputStringType that is compatible with
   * that.
   *
   */
  template <typename OutputStringType>
  static int canonical_decomposition(const codepoint input,
                                     OutputStringType& output) {
    int const * mapping =
      props::canonical_decomposition_mapping::resolve(input);
    int const * begin;
    int const * end;
    int count = 0;
    if (mapping == NULL) {
      begin = &(input.value);
      end = begin;
      end++;
      count = 1;
    } else {
      begin = mapping;
      end = begin;
      while (*end != 0) {
        end++;
        count++;
      }
    }
    utf32ne_string_view from_database
      (std::experimental::basic_string_view<int>(begin, count));
    output.template append<utf32ne_string_view>
      (from_database.codepoint_cbegin(),
       from_database.codepoint_cend());
    return count;
  }

}

#endif
