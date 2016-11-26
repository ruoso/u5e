#ifndef INCLUDED_U5E_CODEPOINT_DECOMPOSITION
#define INCLUDED_U5E_CODEPOINT_DECOMPOSITION

#include <iterator>
#include <algorithm>
#include <experimental/string_view>

#include <u5e/codepoint.hpp>
#include <u5e/props/compatibility_and_canonical_decomposition_mapping.hpp>
#include <u5e/utf32ne_string_view.hpp>

namespace u5e {

  /**
   * \brief Perform codepoint by codepoint decomposition
   *
   * This is one step of the normalization process, you probably want
   * to use that instead.
   *
   * This implements only the logic of dealing with the resolved data,
   * the actual database resolution is a template parameter.
   *
   * This is meant to be used as an operation for u5e::filter.
   * 
   * \tparam PropResolver the function that resolves the input
   * codepoint into a sequence of decomposed codepoints.
   *
   * \tparam OutputStringType the output string type to be used.
   * Because this reads data from the database, the returned data is
   * utf32ne, so you need an OutputStringType that is compatible with
   * that.
   *
   */
  template <typename PropResolver, typename OutputStringType>
  inline int codepoint_decomposition
  (const codepoint input,
   OutputStringType& output,
   PropResolver& resolver) {
    int const * mapping = resolver(input);
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
