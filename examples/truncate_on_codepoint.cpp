
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
#include <algorithm>
#include <iostream>
#include <string>
#include <u5e/utf8_string.hpp>
using std::string;
using u5e::utf8_string;
int main(int argc, char** argv) {
  // the original string
  string str("Ola\xCC\x81!");

  // we find the point on the native string where we want to truncate.
  // Count 4 in octets leaves us in the middle of a codepoint
  string::const_iterator stri = str.cbegin();
  std::advance(stri, 4);
  
  // now we produce the output string truncated at where we want.
  // note that this assumes that the text was already in utf8. this is
  // not a conversion operator, it just makes sure the append happens
  // while respecting the codepoint boundaries in the utf8 text.
  utf8_string output("");
  output.append<string>(str.cbegin(), stri);

  std::cout << output.underlying_string << std::endl;
}
/**
 * \endcode
 */
