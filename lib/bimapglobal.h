#ifndef BIMAP_GLOBAL_H
#define BIMAP_GLOBAL_H

#include "config.h"

/**********************************
 * Library management
 *********************************/
#ifdef __GNUC__
#   if defined(BIMAP_LIB)
#       define BIMAP_EXPORT __attribute__((visibility("default")))
#   else
#       define BIMAP_EXPORT
#   endif
#else
#   if defined(BIMAP_LIB)
#       define BIMAP_EXPORT __declspec(dllexport)
#   else
#       define BIMAP_EXPORT __declspec(dllimport)
#   endif
#endif

/**********************************
 * Deprecations warnings
 *********************************/
#define BIMAP_DEPREC              [[deprecated]]          /**< Use to mark a method as deprecated. \n\code{.cpp}BIMAP_DEPREC void myOldFct(); \endcode */
#define BIMAP_DEPREC_X(reason)    [[deprecated(reason)]] 	/**< Use to mark a method as deprecated and specify a reason. \n\code{.cpp}BIMAP_DEPREC_X("Use myNewFct() instead") void myOldFunc(); \endcode */

/**********************************
 * Custom macros used to detect custom
 * built-in functions
 * Sources:
 * - MSVC: No equivalent
 * - GCC: https://gcc.gnu.org/onlinedocs/gcc-13.2.0/cpp/_005f_005fhas_005fbuiltin.html
 * - Clang: https://clang.llvm.org/docs/LanguageExtensions.html#has-builtin
 *********************************/
#if defined(__GNUC__) || defined(__clang__)
#   define BIMAP_BUILTIN(x)  __has_builtin(x)
#else
#   define BIMAP_BUILTIN(x)  0
#endif

/**********************************
 * Custom macros in order to
 * not trigger warning on expected
 * behaviour
 *********************************/
#define BIMAP_FALLTHROUGH  [[fallthrough]]    /**< Indicates that the fall through from the previous case label is intentional and should not be diagnosed by a compiler that warns on fallthrough */

#endif // BIMAP_GLOBAL_H