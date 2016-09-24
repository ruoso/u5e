#ifndef INCLUDED_U5E_UTF32NE_STRING_VIEW
#define INCLUDED_U5E_UTF32NE_STRING_VIEW

#include <experimental/string_view>
#include <u5e/basic_encodedstring.hpp>
#include <u5e/utf32ne.hpp>

namespace u5e {
  typedef basic_encodedstring<u5e::utf32ne,
			      std::experimental::basic_string_view<int>>
  utf32ne_string_view;
};

#endif
