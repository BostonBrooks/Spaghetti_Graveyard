/**
 * @file
 *
 * @ingroup 
 * @brief Some data for launching and updating the window
 */
 
#ifndef WINDOW_H
#define WINDOW_H

//-----------------------------INCLUDES----------------------------//

#include "../headers/system_includes.h"
#include "../headers/constants.h"
#include "../headers/media.h"

//-----------------------------CONSTANTS----------------------------//

//Constants may be found in constants.h

//-----------------------------STRUCURES------------------------------//

//-----------------------------GLOBALS----------------------------//

/** represents the window */
extern sfRenderWindow* window;


//-----------------------------FUNCTIONS--------------------------//

/** creates the window */
int Window_Init(void);

/** TODO add text */
int Display_Decal(void);

/** TODO Window_Display not defined */
int Window_Display(void);

#endif
