#ifndef INCLUDED_U5E_NORMALIZATION_FORM_KD
#define INCLUDED_U5E_NORMALIZATION_FORM_KD

#include <algorithm>
#include <u5e/basic_grapheme.hpp>
#include <u5e/utf32ne_string.hpp>
#include <u5e/filter.hpp>
#include <u5e/compatibility_and_canonical_decomposition.hpp>
#include <u5e/canonical_combining_order.hpp>

namespace u5e {
  /**
   * \brief u5e::filter algorithm for normalizing graphemes
   *
   * This will work by reading an input grapheme iterator and,
   * grapheme by grapheme normalize them in form KD.
   *
   * This will use the unicode database to search for equivalent
   * codepoint sequences.
   */
  template <typename InputStorageType,
            typename OutputStorageType = InputStorageType>
  inline int normalization_form_kd(basic_grapheme<InputStorageType> grapheme,
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

    // finally append the output
    output.template append_from_utf32ne<utf32ne_string>
      (decomposed.codepoint_begin(),
       decomposed.codepoint_end());

    // we re-use the counter from the decomposition filter.
    return count;
  }
}

#endif
