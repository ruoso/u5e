/**
 * \page normalization_form_kd_utf32 Example: Normalize a utf32 string in form KD
 *
 * This example covers the usage of u5e::filter with
 * u5e::normalization_form_kd in order to normalize a utf32 string in
 * the native endianess.
 *
 * \code
 */// Example on how to iterate

#include <u5e/utf32ne_string.hpp>
#include <u5e/filter.hpp>
#include <u5e/normalization_form_kd.hpp>
#include <stdio.h>

int main(int argc, char **argv) {

  u5e::utf32ne_string input({ 0xC4, 0xFB03, 'n' });
  u5e::utf32ne_string output;
  u5e::filter(input.grapheme_begin(), input.grapheme_end(), output,
              u5e::normalization_form_kd<u5e::utf32ne_string>);
    
  // print out the codepoints
  for (u5e::utf32ne_string::const_iterator it = output.codepoint_cbegin();
       it != output.codepoint_cend(); it++ ) {
    printf(" U+%06llx", (long long unsigned int)*it);
  }

  return 0;
}
/**
 * \endcode
 */
