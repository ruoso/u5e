#ifndef INCLUDED_U5E_PROPS_CANONICAL_COMPOSITION_MAPPING
#define INCLUDED_U5E_PROPS_CANONICAL_COMPOSITION_MAPPING

namespace u5e {
  /**
   * \brief codepoint property handling
   */
  namespace props {
    /**
     * \brief Derived property for canonical composition
     *
     * This has the fully resolved canonical composition for
     * characters, including the composition exclusions specified in
     * the standard.
     */
    class canonical_composition_mapping {
    public:
      /**
       * Given a pair of input codepoints a and b returns whether or
       * not that pair has a canonical composition. The composed
       * codepoint is returned via the r_composed pointer if that is
       * the case.
       *
       * \param a the first codepoint in the decomposed pair
       *
       * \param b the second codepoint in the decomposed pair
       *
       * \param r_composed the pointer where the composed codepoint
       * will be set if the return is true.
       */
      static bool resolve(int a, int b, int* r_composed);
    };
  }
}

#endif
