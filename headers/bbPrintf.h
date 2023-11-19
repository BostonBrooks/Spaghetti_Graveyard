/** This header contains custom print functions, assert function
 * Enabled by definitions BBDEBUG and BBVERBOSE */


#ifndef CONSTANTS
#define CONSTANTS
#include "../headers/constants.h"
#endif

#include <stdio.h>
#include <stdarg.h>


static int bbDebug(const char* format, ...){

#ifdef BBDEBUG


    printf("DEBUG: ");
    va_list args;
    va_start(args, format);

    vprintf(format, args);

    va_end (args);
#endif

}


static int bbVerbose(const char* format, ...){

#ifdef BBVERBOSE


    printf("VERBOSE: ");
    va_list args;
    va_start(args, format);

    vprintf(format, args);

    va_end (args);
#endif

}


