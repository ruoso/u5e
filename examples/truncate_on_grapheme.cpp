
/**
 * \page truncate_on_grapheme Example: Truncate a string on grapheme boundary
 *
 * The challenge of truncating a string is that if you operate on the
 * native level, you risk breaking a codepoint in half. And even when
 * you take the codepoint boundaries in consideration, you still risk
 * breaking a grapheme in half.
 *
 * The u5e library provides an easy way to truncate a text, starting
 * from a target native size and finding the correct boundary.
 *
 * \code
 */// Example on how to truncate on correct grapheme boundaries
#include <algorithm>
#include <iostream>
#include <string>
#include <u5e/utf8_string.hpp>
#include <u5e/utf8_string_grapheme_iterator.hpp>
using std::string;
using u5e::utf8_string;
using u5e::utf8_string_grapheme_iterator;
int main(int argc, char** argv) {
  // the original string
  string str("Ola\xCC\x81!");

  // we find the point on the native string where we want to truncate.
  // Count 4 in octets leaves us in the middle of the second codepoint
  // of a grapheme.
  string::const_iterator stri = str.cbegin();
  std::advance(stri, 4);

  // We need to promote the iterators to utf8 iterators.
  utf8_string::const_iterator u8b(str.begin());
  utf8_string::const_iterator u8e(str.end());
  utf8_string::const_iterator u8i(stri);

  // In order to work with graphemes, we need to obtain grapheme
  // iterators.
  utf8_string_grapheme_iterator gb(u8b, u8e);
  utf8_string_grapheme_iterator gi(u8b, u8e, u8i);
  
  // now we produce the output string truncated at where we want.
  // note that this assumes that the text was already in utf8. this is
  // not a conversion operator, it just makes sure the append happens
  // while respecting the codepoint and grapheme boundaries in the
  // utf8 text.
  utf8_string output("");
  output.append(gb, gi);

  std::cout << output.native_string << std::endl;
}
/**
 * \endcode
 */
