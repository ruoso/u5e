
#include <experimental/string_view>
#include <u5e/codepoint.hpp>
#include <u5e/utf8.hpp>
#include <stdio.h>

using std::experimental::string_view;

int main(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    string_view p(argv[i], strlen(argv[i]));
    u5e::utf8<string_view> parameter(p);
    u5e::utf8<string_view>::iterator it = parameter.begin();
    while (it != parameter.end()) {
      printf(" U+%06llx ", *it++);
    }
    printf("\n");
  }
  return 0;
}
