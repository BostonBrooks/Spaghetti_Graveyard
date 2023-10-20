/**
 * @file
 *
 * @ingroup
 * @brief each bbSkin contains INNER_STATES_PER_SKIN animations. These are templates the animations used by bbAIControl objects.
 */

#define BBSKIN


//-----------------------------INCLUDES----------------------------//

#ifndef CONSTANTS
#define CONSTANTS
#include "../headers/constants.h"
#endif

#ifndef SYSTEM_INCLUDES
#define SYSTEM_INCLUDES
#include "../headers/system_includes.h"
#endif

#ifndef VIEWPORT
#define VIEWPORT
#include "../headers/viewport.h"
#endif

#ifndef GEOMETRY
#define GEOMETRY
#include "../headers/geometry.h"
#endif

#ifndef BBDRAWABLE
#define BBDRAWABLE
#include "../headers/bbDrawable.h"
#endif

#ifndef BBDRAWABLE_LISTS
#define BBDRAWABLE_LISTS
#include "../headers/bbDrawable_lists.h"
#endif

#ifndef BBGROUNDSURFACE
#define BBGROUNDSURFACE
#include "../headers/bbGroundSurface.h"
#endif

#ifndef BBSKIN
#define BBSKIN
#include "../headers/bbSkin.h"
#endif

#ifndef MEDIA
#define MEDIA
#include "../headers/media.h"
#endif

//-----------------------------GLOBALS----------------------------//

typedef struct {

    int animations_int [INNER_STATES_PER_SKIN][ANIMATIONS_PER_DRAWABLE];
    int drawfunctions_int [INNER_STATES_PER_SKIN][ANIMATIONS_PER_DRAWABLE];


} bbSkin;

bbSkin bbSkins [NUMBER_OF_SKINS];

//Later we will put animations in a dictionary,
//lookup animations from dictionary then add to skins.

int bbSkin_init() {

    bbSkin* skin = &bbSkins[0];
    skin->animations_int[STATE_IDLE][0] = 24;
    skin->animations_int[STATE_MOVING][0] = 20;
    skin->animations_int[STATE_APPROACHING][0] = 20;
    skin->animations_int[STATE_ATTACKING][0] = 22;
    skin->animations_int[STATE_DEAD][0] = 23;
    skin->animations_int[STATE_STUNNED][0] = 21;

    skin->drawfunctions_int[STATE_IDLE][0] = DRAW_REPEAT_SKIN;
    skin->drawfunctions_int[STATE_MOVING][0] = DRAW_REPEAT_SKIN;
    skin->drawfunctions_int[STATE_APPROACHING][0] = DRAW_REPEAT_SKIN;
    skin->drawfunctions_int[STATE_ATTACKING][0] = DRAW_REPEAT_SKIN;
    skin->drawfunctions_int[STATE_DEAD][0] = DRAW_ONCE_SKIN;
    skin->drawfunctions_int[STATE_STUNNED][0] = DRAW_REPEAT_SKIN;


    for (int i = 0; i < INNER_STATES_PER_SKIN; i++){



        for (int j = 1; j < ANIMATIONS_PER_DRAWABLE; j++){

            skin->animations_int[i][j] = ANIMATION_NONE;
            skin->drawfunctions_int[i][j] = DRAWFUNCTION_NONE;

        }

    }

}