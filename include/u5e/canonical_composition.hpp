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
    typename StorageType::iterator oi(data.codepoint_begin());
    typename StorageType::iterator in = oi;
    typename StorageType::iterator end(data.codepoint_end());

    int a, b, c;
    while (in != end) {
      //
      // grab the codepoint in the current input iterator
      //
      a = *in;
      if ((in + 1) == end) {
        //
        // If this is the last codepoint, it can't be composed, so we
        // just push it to the output as-is.
        //
        *(oi++) = a;
        in++;
      } else {
        //
        // look ahead for the next codepoint
        //
        b = *(in + 1);
        if (u5e::props::canonical_composition_mapping::resolve(a, b, &c)) {
          //
          // If this is a composition, we set it as the current input
          // iterator after advancing, because it may still be
          // composed more.
          //
          *(++in) = c;
          *count = *count + 1;
        } else {
          //
          // If there is no composition, we set it in the output iterator
          //
          *(oi++) = a;
          //
          // And finally advance the input iterator.
          //
          in++;
        }
      }
    }

    return oi;
  };
}

#endif
