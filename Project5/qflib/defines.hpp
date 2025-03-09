/** 
@file  defines.hpp
@brief Library-wide version numbers, macro, and constant definitions
*/

#ifndef QF_DEFINES_HPP
#define QF_DEFINES_HPP

/** version string */
#ifdef NDEBUG
#define QF_VERSION_STRING "0.5.0"
#else
#define QF_VERSION_STRING "0.5.0-debug"
#endif

/** version numbers */
#define QF_VERSION_MAJOR 0
#define QF_VERSION_MINOR 5
#define QF_VERSION_REVISION 0

/** Macro for namespaces */
#define BEGIN_NAMESPACE(x)	namespace x {
#define END_NAMESPACE(x)	}

/** Macro for Extern C */
#define BEGIN_EXTERN_C  extern "C" {
#define END_EXTERN_C    }

/** number of days in a year */
#define DAYS_PER_YEAR 365.25

/** number of seconds in a day */
#define SECS_PER_DAY 86400. //(24.*60*60)
#define SECS_PER_DAY_LONG 86400L

/** number of seconds in a year */
#define SECS_PER_YEAR (SECS_PER_DAY*DAYS_PER_YEAR)

/** number of seconds in an hour */
#define SECS_PER_HOUR 3600.

// math constants
#define _USE_MATH_DEFINES
#include <cmath>

// extra math constants
/** 1/sqrt(2*pi) */
#define M_1_SQRT2PI  0.398942280401432678

#endif // QF_DEFINES_HPP
