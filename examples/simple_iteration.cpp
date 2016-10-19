/**
 * \page simple_iteration Example: Iterate over codepoints in utf8 text
 *
 * This example covers the basic usage of iterating over utf8 text
 * codepoint by codepoint.
 *
 * \code
 */// Example on how to iterate

#include <experimental/string_view>
#include <u5e/utf8_string_view.hpp>
#include <stdio.h>

using std::experimental::string_view;

int main(int argc, char **argv) {
  // for each argument
  for (int i = 1; i < argc; i++) {

    // get a string_view
    string_view p(argv[i], strlen(argv[i]));

    // get a utf8_string_view::const_iteator
    u5e::utf8_string_view::const_iterator it = p.begin();

    // Iterate until the end
    while (it != p.end()) {

      // the value dereferenced is the codepoint, not octets even if
      // the original text had "wide" chars.
      printf(" U+%06llx ", (long long unsigned int)*it++);
      
    }
    
    printf("\n");
  }
  return 0;
}
/**
 * \endcode
 */
