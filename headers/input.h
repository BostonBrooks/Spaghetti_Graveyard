/**
 * @file
 *
 * @ingroup 
 * @brief Input key presses and mouse clicks
 */
 
 #define INPUT


//-----------------------------INCLUDES----------------------------//


#ifndef PROMPT
#define PROMPT
#include "../headers/prompt.h"
#endif

#ifndef SYSTEM_INCLUDES
#define SYSTEM_INCLUDES
#include "../headers/system_includes.h"
#endif


#ifndef GEOMETRY
#define GEOMETRY
#include "../headers/geometry.h"
#endif

#ifndef WINDOW
#define WINDOW
#include "../headers/window.h"
#endif
//-----------------------------GLOBALS----------------------------//

extern bbScreenCoords mouse_screen_position;

extern bbMapCoords mouse_map_position;

extern int right_button_down;
//if right button is down, player AI will set goal point to mouse_map_position
extern int left_button_down;
//if button is clicked the player AI will attack the ground at that point


//-----------------------PLACEHOLDER FUNCTIONS--------------------//


//-----------------------------FUNCTIONS--------------------------//

int input_process(void);
