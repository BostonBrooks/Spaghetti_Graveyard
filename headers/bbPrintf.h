/** This header contains custom print functions
 * Enabled by definitions BBDEBUG and BBVERBOSE
 * May be defined on a file-by=file basis */


#ifndef BBPRINTF_H
#define BBPRINTF_H

#include "../headers/constants.h"
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

#endif
