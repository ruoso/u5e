
#include <experimental/string_view>
#include <u5e/utf8_string_view.hpp>
#include <stdio.h>

using std::experimental::string_view;

int main(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    string_view p(argv[i], strlen(argv[i]));
    u5e::utf8_string_view::const_iterator it = p.begin();
    while (it != p.end()) {
      printf(" U+%06llx ", *it++);
    }
    printf("\n");
  }
  return 0;
}
