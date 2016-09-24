#ifndef INCLUDED_U5E_UTF32_NATIVE_STRING_VIEW
#define INCLUDED_U5E_UTF32_NATIVE_STRING_VIEW

#include <experimental/string_view>
#include <u5e/basic_encodedstring.hpp>
#include <u5e/utf32_native.hpp>

namespace u5e {
  typedef basic_encodedstring<u5e::utf32_native,
			      std::experimental::basic_string_view<int>>
  utf32_native_string_view;
};

#endif
