/**
 * @file
 *
 * @ingroup 
 * @brief This header file contains includes for interacting with the operating system
 */

#ifndef SYSTEM_INCLUDES_H
#define SYSTEM_INCLUDES_H


#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
//#include <err.h>

void err( int eval,
          const char *fmt, ...);

#endif
