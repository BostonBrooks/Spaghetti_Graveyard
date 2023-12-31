/**
 * @file
 *
 * @ingroup 
 * @brief Code for updating AI is stored in ./source/AI. There is one file per unit type. This file includes all of those files and initialises a vtable containing the functions 
 */

#include "../headers/bbAIControl_init.h"

//-----------------------------INCLUDES----------------------------//


#include "../headers/bbAIControl.h"
#include "../headers/constants.h"
#include "../headers/geometry.h"
#include "../headers/bbAIControl.h"
#include "../headers/bbMessage.h"
#include "../headers/bbDrawable.h"
#include "../headers/nelder_mead_deprecated.h"
#include "../headers/angles.h"

//one #include per ai type

#include "../AI/AI_null.h"
#include "../AI/AI_fox.h"
#include "../AI/AI_Yeti.h"
#include "../AI/AI_Tortoise.h"
#include "../AI/AI_Snail.h"
#include "../AI/PLAYER.h"
#include "../AI/AI_Arrow.h"


//-----------------------------CODE------------------------------//

//define table of ai constructors
//define table of ai functions
//define table of RPCs

int (*bbAI_constructor_vtable[NUMBER_OF_EXTERNAL_STATES])(bbMapCoords mc);
int (*bbAI_update_vtable[NUMBER_OF_EXTERNAL_STATES])(bbAIControl* aicontroller);
int (*bbAI_RPC_vtable[NUMBER_OF_EXTERNAL_STATES])(bbAIControl* aicontroller, bbMessage* message);

int bbAIControl_init(){

//initialise table of ai constructors
//initialise table of ai functions
//initialise table of RPCs

    bbAI_constructor_vtable[AI_NULL] = AI_null_new;
    bbAI_update_vtable[AI_NULL] = AI_null_update;
    bbAI_RPC_vtable[AI_NULL] = AI_null_RPC;


    bbAI_constructor_vtable[AI_FOX] = AI_fox_new;
    bbAI_update_vtable[AI_FOX] = AI_fox_update;
    bbAI_RPC_vtable[AI_FOX] = AI_fox_RPC;


    bbAI_constructor_vtable[AI_YETI] = AI_yeti_new;
    bbAI_update_vtable[AI_YETI] = AI_yeti_update;
    bbAI_RPC_vtable[AI_YETI] = AI_yeti_RPC;


    bbAI_constructor_vtable[AI_TORTOISE] = AI_tortoise_new;
    bbAI_update_vtable[AI_TORTOISE] = AI_tortoise_update;
    bbAI_RPC_vtable[AI_TORTOISE] = AI_tortoise_RPC;

    bbAI_constructor_vtable[AI_SNAIL] = AI_cow_new;
    bbAI_update_vtable[AI_SNAIL] = AI_cow_update;
    bbAI_RPC_vtable[AI_SNAIL] = AI_cow_RPC;


    bbAI_constructor_vtable[PLAYER_20230829] = PLAYER_new;
    bbAI_update_vtable[PLAYER_20230829] = PLAYER_update;
    bbAI_RPC_vtable[PLAYER_20230829] = PLAYER_RPC;

    bbAI_constructor_vtable[AI_ARROW] = AI_arrow_new;
    bbAI_update_vtable[AI_ARROW] = AI_arrow_update;
    bbAI_RPC_vtable[AI_ARROW] = AI_arrow_RPC;
}



