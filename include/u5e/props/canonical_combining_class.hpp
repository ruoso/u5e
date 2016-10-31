#ifndef INCLUDED_U5E_PROPS_CANONICAL_COMBINING_CLASS
#define INCLUDED_U5E_PROPS_CANONICAL_COMBINING_CLASS

namespace u5e {
  /**
   * \brief codepoint property handling
   */
  namespace props {
    /**
     * \brief Canonical_Combining_Class attribute
     */
    class canonical_combining_class {
    public:
      /**
       * Return the Canonical_Combining_class for this codepoint
       */
      static int resolve(int input);
    };
  }
}

#endif
