#if defined(_MSC_VER)
#include "config_msvc.h"
#elif defined(__MINGW32__)
#include "config_mingw.h"
#elif defined(__MACH__)
#include "config_darwin.h"
#else
#include "config_unix.h"
#endif
