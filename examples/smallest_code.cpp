#include <u5e/utf8_iterator.hpp>

int main(int argc, char** argv) {
  u5e::utf8_iterator<const char*> it(argv[1]);
  return (*it).value;
}
