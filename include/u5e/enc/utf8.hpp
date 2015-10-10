#ifndef INCLUDED_U5E_ENC_UTF8
#define INCLUDED_U5E_ENC_UTF8

#include <u5e/buffer.hpp>
#include <u5e/codepoint.hpp>

namespace u5e {
  namespace enc {
    /**
     * u5e::enc::utf8
     *
     * Handles utf8 encoded data
     */
    class utf8 {
    public:
      typedef u5e::buffer<char> enc_buffer_type;
      typedef enc_buffer_type::iterator iterator;
      typedef enc_buffer_type::reverse_iterator reverse_iterator;
      static const enc_buffer_type::size_type min_codepoint_size = 1;
      static const enc_buffer_type::size_type max_codepoint_size = 4;
      static const enc_buffer_type::size_type max_bmp_codepoint_size = 3;
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
