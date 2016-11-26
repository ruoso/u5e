/**
 * \page normalization_form_kc Example: Normalize a utf8 string in form C
 *
 * This example covers the usage of u5e::filter with
 * u5e::normalization_form_kc in order to normalize a utf8 string.
 *
 * \code
 */// Example on how to iterate

#include <u5e/utf8_string.hpp>
#include <u5e/filter.hpp>
#include <u5e/normalization_form_kc.hpp>
#include <stdio.h>

int main(int argc, char **argv) {

  // for each argument
  for (int i = 1; i < argc; i++) {

    // get a utf8_string_view
    u5e::utf8_string input(argv[i]);
    u5e::utf8_string output;
    u5e::filter(input.grapheme_begin(), input.grapheme_end(), output,
                u5e::normalization_form_kc<u5e::utf8_string>);
    
    // print out the codepoints
    for (u5e::utf8_string::const_iterator it = output.codepoint_cbegin();
         it != output.codepoint_cend(); it++ ) {
      // the value dereferenced is the codepoint, not octets even if
      // the original text had "wide" chars.
      printf(" U+%06llx", (long long unsigned int)*it);
    }

    printf("\n");
  }
  return 0;
}
/**
 * \endcode
 */
