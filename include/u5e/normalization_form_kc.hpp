#ifndef INCLUDED_U5E_NORMALIZATION_FORM_KC
#define INCLUDED_U5E_NORMALIZATION_FORM_KC

#include <algorithm>
#include <u5e/basic_grapheme.hpp>
#include <u5e/utf32ne_string.hpp>
#include <u5e/filter.hpp>
#include <u5e/compatibility_and_canonical_decomposition.hpp>
#include <u5e/canonical_combining_order.hpp>
#include <u5e/canonical_composition.hpp>

namespace u5e {
  /**
   * \brief u5e::filter algorithm for normalizing graphemes
   *
   * This will work by reading an input grapheme iterator and,
   * grapheme by grapheme normalize them in form KC.
   *
   * This will use the unicode database to search for equivalent
   * codepoint sequences.
   */
  template <typename InputStorageType,
            typename OutputStorageType = InputStorageType>
  inline int normalization_form_kc(basic_grapheme<InputStorageType> grapheme,
                                   OutputStorageType& output) {

    // first step is to decompose the grapheme
    utf32ne_string decomposed;
    int count = u5e::filter
      (grapheme.codepoint_begin(),
       grapheme.codepoint_end(),
       decomposed,
       compatibility_and_canonical_decomposition<utf32ne_string>);

    // then sort based on canonical combining class
    std::sort(decomposed.codepoint_begin(), decomposed.codepoint_end(),
              canonical_combining_order);

    // finally recompose. we will do that in-place on the decomposed
    // string, since we never have to look back.
    int compositions = 0;
    utf32ne_string::iterator oi_begin(decomposed.codepoint_begin());
    utf32ne_string::iterator oi
      (u5e::canonical_composition(decomposed,&compositions));

    // finally append the output
    output.template append_from_utf32ne<utf32ne_string>
      (oi_begin, oi);

    // we re-use the counter from the decomposition filter and
    // subtract how many pair were composed into a single codepoint.
    return count - compositions;
  }
}

#endif
