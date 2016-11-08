#ifndef INCLUDED_U5E_NORMALIZATION_FORM_C
#define INCLUDED_U5E_NORMALIZATION_FORM_C

#include <algorithm>
#include <u5e/basic_grapheme.hpp>
#include <u5e/utf32ne_string.hpp>
#include <u5e/filter.hpp>
#include <u5e/canonical_decomposition.hpp>
#include <u5e/canonical_combining_order.hpp>
#include <u5e/props/canonical_composition_mapping.hpp>

namespace u5e {
  /**
   * \brief u5e::filter algorithm for normalizing graphemes
   *
   * This will work by reading an input grapheme iterator and,
   * grapheme by grapheme normalize them in form C.
   *
   * This will use the unicode database to search for equivalent
   * codepoint sequences.
   */
  template <typename InputStorageType,
            typename OutputStorageType = InputStorageType>
  inline int normalization_form_c(basic_grapheme<InputStorageType> grapheme,
                                  OutputStorageType& output) {

    // first step is to decompose the grapheme
    utf32ne_string decomposed;
    int count = u5e::filter(grapheme.codepoint_begin(),
                            grapheme.codepoint_end(),
                            decomposed,
                            canonical_decomposition<utf32ne_string>);

    // then sort based on canonical combining class
    std::sort(decomposed.codepoint_begin(), decomposed.codepoint_end(),
              canonical_combining_order);

    // finally recompose. we will do that in-place on the decomposed
    // string, since we never have to look back.
    utf32ne_string::iterator oi_begin(decomposed.codepoint_begin());
    utf32ne_string::iterator oi(decomposed.codepoint_begin());
    utf32ne_string::const_iterator input(decomposed.codepoint_cbegin());
    utf32ne_string::const_iterator input_end(decomposed.codepoint_cend());
    while (input != input_end) {
      int a = *(input++);
      if (input == input_end) {
        // there is no b.
        *(oi++) = a;
      } else {
        // look ahead for the next codepoint
        int b = *input;
        int composed;
        if (u5e::props::canonical_composition_mapping::resolve(a, b, &composed)) {
          *(oi++) = composed;
          ++input;
          count--;
        } else {
          *(oi++) = a;
        }
      }
    }
    
    // finally append the output
    output.template append_from_utf32ne<utf32ne_string>
      (oi_begin, oi);

    // we re-use the counter from the decomposition filter.
    return count;
  }
}

#endif
