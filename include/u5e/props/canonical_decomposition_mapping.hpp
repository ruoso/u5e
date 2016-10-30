#ifndef INCLUDED_U5E_PROPS_CANONICAL_DECOMPOSITION_MAPPING
#define INCLUDED_U5E_PROPS_CANONICAL_DECOMPOSITION_MAPPING

namespace u5e {
  /**
   * \brief codepoint property handling
   */
  namespace props {
    /**
     * \brief Subset of Decomposition_Mapping attribute
     *
     * This recursively resolves the canonical decomposition mapping.
     * The returned data is fully canonically decomposed.
     */
    class canonical_decomposition_mapping {
    public:
      /**
       * Perform the decomposition. Returns NULL if the character has
       * no decomposition.
       *
       * The returned int array will be zero terminated.
       */
      static int const * const resolve(int input);
    };
  }
}

#endif
