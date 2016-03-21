#ifndef INCLUDED_U5E_BASIC_ENCODEDSTRINGBUF
#define INCLUDED_U5E_BASIC_ENCODEDSTRINGBUF

#include <u5e/basic_encodedstreambuf.hpp>
#include <sstream>

namespace u5e {
  template <typename Encoding>
  using basic_encodedstringbuf = basic_encodedstreambuf<Encoding, std::basic_stringbuf<typename Encoding::encoded_unit>>;
};

#endif
