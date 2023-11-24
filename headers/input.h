/**
 * @file
 *
 * @ingroup 
 * @brief Input key presses and mouse clicks
 */
 
#ifndef INPUT_H
#define INPUT_H

//-----------------------------INCLUDES----------------------------//


#include "../headers/prompt.h"
#include "../headers/system_includes.h"
#include "../headers/geometry.h"
#include "../headers/window.h"

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

#endif
