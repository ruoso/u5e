/**
 * \page grapheme_iteration Example: Iterate over graphemes in utf8 text
 *
 * This example covers the basic usage of iterating over utf8 text
 * grapheme by grapheme.
 *
 * \code
 */// Example on how to iterate

#include <experimental/string_view>
#include <u5e/utf8_string_view.hpp>
#include <u5e/utf8_string_view_grapheme.hpp>
#include <u5e/utf8_string_view_grapheme_iterator.hpp>
#include <stdio.h>

using std::experimental::string_view;
using u5e::utf8_string_view;
using u5e::utf8_string_view_grapheme;
using u5e::utf8_string_view_grapheme_iterator;

int main(int argc, char **argv) {

  // for each argument
  for (int i = 1; i < argc; i++) {

    // get a utf8_string_view
    utf8_string_view p(argv[i]);

    // get the grapheme iterator from that
    // Iterate grapheme by grapheme
    for (utf8_string_view_grapheme_iterator gi = p.grapheme_begin();
         gi != p.grapheme_end(); gi++) {
      utf8_string_view_grapheme g = *gi;
      printf("[");

      // then iterate the codepoints inside that grapheme
      for (utf8_string_view::const_iterator it = g.codepoint_begin();
           it != g.codepoint_end(); it++ ) {
        // the value dereferenced is the codepoint, not octets even if
        // the original text had "wide" chars.
        printf(" U+%06llx", (long long unsigned int)*it);
      }

      printf(" ]");
    }

    printf("\n");
  }
  return 0;
}
/**
 * \endcode
 */
