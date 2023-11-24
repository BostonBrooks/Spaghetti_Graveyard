/**
 * @file
 *
 * @ingroup 
 * @brief Code for updating AI is stored in ./source/AI. There is one file per unit type. This file includes all of those files and initialises a vtable containing the functions 
 */

#ifndef BBAICONTROL_INIT_H
#define BBAICONTROL_INIT_H

#include "../headers/constants.h"
#include "../headers/geometry.h"
#include "../headers/bbAIControl.h"
#include "../headers/bbMessage.h"



//declare table of ai constructors
//declare table of ai functions
//declare table of RPCs


extern int (*bbAI_constructor_vtable[NUMBER_OF_EXTERNAL_STATES])(bbMapCoords mc);
extern int (*bbAI_update_vtable[NUMBER_OF_EXTERNAL_STATES])(bbAIControl* aicontroller);
extern int (*bbAI_RPC_vtable[NUMBER_OF_EXTERNAL_STATES])(bbAIControl* aicontroller, bbMessage* message);


//initialise table of ai constructors
//initialise table of ai functions
//initialise table of RPCs
int bbAIControl_init();





#endif
