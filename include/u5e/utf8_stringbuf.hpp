#ifndef INCLUDED_U5E_UTF8_ENCODEDSTRINGBUF
#define INCLUDED_U5E_UTF8_ENCODEDSTRINGBUF

#include <u5e/basic_encodedstringbuf.hpp>
#include <u5e/utf8.hpp>
#include <sstream>

namespace u5e {
  typedef basic_encodedstringbuf<utf8> utf8_stringbuf;
};

#endif
