#ifndef INCLUDED_U5E_BUFFER_HPP
#define INCLUDED_U5E_BUFFER_HPP

#include <experimental/string_view>

/**
 * u5e::buffer
 *
 * When traversing this buffer you may end up splitting a codepoint
 * apart and generating invalid text. This should only be consumed by
 * the encoding implementation.
 *
 * This offers a local class for string_view, such that we hide the
 * fact that we are using an experimental feature. Also, it
 * technically allows us to offer a real implementation if we decide
 * not to use the experimental version.
 */
namespace u5e {
  template <class CharT, class Traits = std::char_traits<CharT> >
  using buffer = std::experimental::basic_string_view<CharT, Traits>;
}

#endif
