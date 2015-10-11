
#include <u5e/codepoint.hpp>
#include <u5e/encoded_buffer.hpp>
#include <u5e/enc/utf8.hpp>
#include <stdio.h>

int main(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    u5e::encoded_buffer<u5e::enc::utf8> parameter(argv[i], strlen(argv[i]));
    u5e::enc::utf8::iterator it = parameter.begin();
    while (it != parameter.end()) {
      printf(" U+%06llx ", *it++);
    }
    printf("\n");
  }
  return 0;
}
