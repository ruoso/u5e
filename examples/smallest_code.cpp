/**
 * \page smallest_code Example: using utf8_iterator with const char*
 *
 * This example shows that it's possible to use the utf8 iterator with a
 * bare const char*, even without getting a string or a string_view.
 *
 * \code
 */// example

#include <u5e/utf8_iterator.hpp>
int main(int argc, char** argv) {
  // you can instantiate utf8_iterator even with const char*
  u5e::utf8_iterator<const char*> it(argv[1]);
  return *it;
}

/**
 * \endcode
 */

