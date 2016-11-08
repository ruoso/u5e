#ifndef INCLUDED_U5E_CANONICAL_COMPOSITION
#define INCLUDED_U5E_CANONICAL_COMPOSITION

#include <u5e/props/canonical_composition_mapping.hpp>

namespace u5e {
  /**
   * \brief performs in-place canonical composition.
   *
   * This will return the iterator in the end position after the
   * composition.
   *
   * \tparam StorageType the storage type where to apply it.
   *
   * Must support codepoint_begin, codepont_cbegin, codepoint_end,
   * codepoint_cend, as well as the member types iterator and
   * const_iterator.  It is also a requirement that you should be able
   * to write to it as you read it, which means that this must only be
   * used in utf32 iterators, otherwise the output may race ahead of
   * the input.
   *
   * \param data the object where the canonical composition will be
   * performed.
   *
   * \param count return pointer for how many compositions were performed
   */
  template <typename StorageType>
  typename StorageType::iterator
  inline canonical_composition(StorageType& data, int* count) {
    typename StorageType::iterator oi_begin(data.codepoint_begin());
    typename StorageType::iterator oi(data.codepoint_begin());
    typename StorageType::const_iterator input(data.codepoint_cbegin());
    typename StorageType::const_iterator input_end(data.codepoint_cend());

    while (input != input_end) {
      int a = *(input++);
      if (input == input_end) {
        // there is no b.
        *(oi++) = a;
      } else {
        // look ahead for the next codepoint
        int b = *input;
        int c;
        if (u5e::props::canonical_composition_mapping::resolve(a, b, &c)) {
          *(oi++) = c;
          ++input;
          *count = *count + 1;
        } else {
          *(oi++) = a;
        }
      }
    }

    return oi;
  };
}

#endif
