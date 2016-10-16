#ifndef U5E_VERSION
#define U5E_VERSION

/**
 * \brief main u5e namespace
 */
namespace u5e {
  /**
   * \brief introspection over the vesion of the library
   * both at compile time and at runtime.
   */
  namespace version {
    /**
     * \brief namespace with compile-time-constant version declaration
     */
    namespace compile_time {
      //@{
      /**
       * Compile-time version definition
       */
      constexpr int major = 0;
      constexpr int minor = 0;
      constexpr int patch = 0;
      //@}
    }
    /**
     * \brief introspection for run-time version declaration
     * To test which version of the library are you linking against
     */
    class run_time {
    public:
      //@{
      /**
       * \brief Run-time introspection for library version
       */
      static const int major;
      static const int minor;
      static const int patch;
      //@}
    };
  }
}

#endif
