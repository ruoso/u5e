
#include <algorithm>
#include <iostream>
#include <string>
#include <u5e/utf8_bounds.hpp>
#include <u5e/utf8_string.hpp>
#include <u5e/utf8_string_grapheme.hpp>
#include <u5e/utf8_string_grapheme_iterator.hpp>

using std::string;
using u5e::utf8_bounds;
using u5e::utf8_string;
using u5e::utf8_string_grapheme;
using u5e::utf8_string_grapheme_iterator;

/**
 * \page truncate_on_codepoint Example: Truncate a string on codepoint boundary
 *
 * The challenge of truncating a string is that if you operate on the
 * native level, you risk breaking a codepoint in half.
 *
 * The u5e library provides an easy way to truncate a text, starting
 * from a target native size and finding the correct boundary.
 *
 * \code
 */// Example on how to truncate on correct codepoint boundaries
int main(int argc, char** argv) {
  // the original string
  utf8_string u8str("Ola\xCC\x81!");

  // we find the point on the native string where we want to truncate.
  // Count 4 in octets leaves us in the middle of a codepoint
  std::string::const_iterator stri = u8str.underlying_string.cbegin();
  std::advance(stri, 4);
  
  // now we produce the output string truncated at where we want.
  utf8_string output("");
  output.append<string>(u8str.cbegin(), stri);

  std::cout << output.underlying_string << std::endl;
}
/**
 * \endcode
 */
