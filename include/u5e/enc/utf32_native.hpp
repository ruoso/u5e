#ifndef INCLUDED_U5E_ENC_UTF32_NATIVE_HPP
#define INCLUDED_U5E_ENC_UTF32_NATIVE_HPP

#include <u5e/buffer.hpp>
#include <u5e/codepoint.hpp>

namespace u5e {
  namespace enc {
    /**
     * u5e::enc::utf32_native
     *
     * The native utf32 encoding is built with the native 32 bit
     * integer type. It is specially more useful for cases where
     * you need to do extensive manipulation on text, since it
     * allows you to have constant random access time.
     */
    class utf32_native {
    public:
      typedef u5e::buffer<u5e::codepoint> enc_buffer_type;
      typedef enc_buffer_type::iterator iterator;
      typedef enc_buffer_type::reverse_iterator reverse_iterator;
      static const enc_buffer_type::size_type min_codepoint_size = 1;
      static const enc_buffer_type::size_type max_codepoint_size = 1;
      static const enc_buffer_type::size_type max_bmp_codepoint_size = 1;
      static const enc_buffer_type::size_type max_ascii_codepoint_size = 1;

      static inline iterator begin(enc_buffer_type raw_buffer) {
        return raw_buffer.begin();
      }

      static inline iterator end(enc_buffer_type raw_buffer) {
        return raw_buffer.end();
      }
    };
  }
}

#endif
