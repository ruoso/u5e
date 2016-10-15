#ifndef U5E_VERSION
#define U5E_VERSION

namespace u5e {
  /**
   * Offer introspection over the vesion of the library both at
   * compile time and at runtime.
   */
  namespace version {
    // Compile-time version definition
    static const int major = 0;
    static const int minor = 0;
    static const int patch = 0;

    // Run-time introspection
    extern int lib_major;
    extern int lib_minor;
    extern int lib_patch;
  }
}

#endif
