/**
 * @file
 *
 * @ingroup
 * @brief each bbSkin contains INNER_STATES_PER_SKIN animations. These are templates the animations used by bbAIControl objects.
 */

#include "../headers/bbSkin.h"


//-----------------------------INCLUDES----------------------------//

#include "../headers/constants.h"
#include "../headers/system_includes.h"
#include "../headers/viewport.h"
#include "../headers/geometry.h"
#include "../headers/bbDrawable.h"
#include "../headers/bbDrawable_lists.h"
#include "../headers/bbGroundSurface.h"
#include "../headers/bbSkin.h"
#include "../headers/media.h"


//-----------------------------GLOBALS----------------------------//


bbSkin bbSkins [NUMBER_OF_SKINS];

//Later we will put animations in a dictionary,
//lookup animations from dictionary then add to skins.

int bbSkin_init() {

    bbSkin* skin = &bbSkins[0];
    skin->animations_int[STATE_IDLE][0] = 17;
    skin->animations_int[STATE_MOVING][0] = 17;
    skin->animations_int[STATE_APPROACHING][0] = 17;
    skin->animations_int[STATE_ATTACKING][0] = 17;
    skin->animations_int[STATE_DEAD][0] = 17;
    skin->animations_int[STATE_STUNNED][0] = 17;

    skin->drawfunctions_int[STATE_IDLE][0] = DRAW_REPEAT_SKIN;
    skin->drawfunctions_int[STATE_MOVING][0] = DRAW_REPEAT_SKIN;
    skin->drawfunctions_int[STATE_APPROACHING][0] = DRAW_REPEAT_SKIN;
    skin->drawfunctions_int[STATE_ATTACKING][0] = DRAW_ONCE_SKIN;
    skin->drawfunctions_int[STATE_DEAD][0] = DRAW_ONCE_SKIN;
    skin->drawfunctions_int[STATE_STUNNED][0] = DRAW_REPEAT_SKIN;


    for (int i = 0; i < INNER_STATES_PER_SKIN; i++){



        for (int j = 1; j < ANIMATIONS_PER_DRAWABLE; j++){

            skin->animations_int[i][j] = ANIMATION_NONE;
            skin->drawfunctions_int[i][j] = DRAWFUNCTION_NONE;

        }

    }

}