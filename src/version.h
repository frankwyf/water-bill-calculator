/**
 * @file version.h
 * @brief Single source of truth for the project version string.
 *
 * Bump these macros when cutting a release; the build system and
 * runtime help text both pick up the values from here automatically.
 */
#ifndef VERSION_H
#define VERSION_H

#define WBC_VERSION_MAJOR 1
#define WBC_VERSION_MINOR 0
#define WBC_VERSION_PATCH 0

/** Dot-separated version string, e.g. "1.0.0". */
#define WBC_VERSION "1.0.0"

/** Programme name, used in help and error messages. */
#define WBC_PROGNAME "water_bill"

#endif /* VERSION_H */
