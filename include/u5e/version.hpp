#ifndef U5E_VERSION
#define U5E_VERSION

namespace u5e {
  struct version {
    // Major version, avaialable at compile time
    static const int major = 0;
    // Minor version, also available at compile time
    static const int minor = 0;
    // Patch version, only available at run time
    static const int patch;
  };
}

#endif
