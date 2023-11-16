
#ifndef SYSTEM_INCLUDES
#define SYSTEM_INCLUDES
#include "../headers/system_includes.h"
#endif


#ifndef ANGLES
#define ANGLES
#include "../headers/angles.h"
#endif

#ifndef CONSTANTS
#define CONSTANTS
#include "../headers/constants.h"
#endif

#ifndef GEOMETRY
#define GEOMETRY
#include "../headers/geometry.h"
#endif

#ifndef BBAICONTROL
#define BBAICONTROL
#include "../headers/bbAIControl.h"
#endif

#ifndef BBMESSAGE
#define BBMESSAGE
#include "../headers/bbMessage.h"
#endif

#ifndef BBDRAWABLE
#define BBDRAWABLE
#include "../headers/bbDrawable.h"
#endif

#ifndef BBDRAWABLE
#define BBDRAWABLE
#include "../headers/bbDrawable.h"
#endif


#ifndef SUM_FORCES
#define SUM_FORCES
#include "../headers/sum_forces.h"
#endif

extern int Current_Time;
extern int player_int;
int damage_player(int);

int AI_arrow_new(bbMapCoords mc){

    //#ifdef DEBUG
    //printf("Creating a tortoise AI object\n");
    //#endif

    int drawable_int = bbDrawable_new(mc);
    bbDrawable* drawable = bbDrawable_Pool_Lookup(drawable_int);


    drawable->skin = 0;
    drawable->state = STATE_MOVING;
    drawable->animation[0] = 21;
    drawable->angle[0] = 0;
    drawable->frame[0] = 0;
    drawable->drawfunction[0] = DRAW_UNIT;
    drawable->start_time = 0;
    drawable->avoidance_radius = POINTS_PER_TILE;

    drawable->target_location.i = mc.i + POINTS_PER_SQUARE;
    drawable->target_location.j = mc.j + POINTS_PER_SQUARE;
    drawable->target_location.k = mc.k;


    drawable->health                = 100;
    drawable->max_health            = 100;
    drawable->display_health_until  = -1;
    drawable->health_bar_height     = 200;
    drawable->health_bar_width      = 5;
    drawable->health_bar_length     = 60;

    bbIntRect Hit_Box;
    Hit_Box.top = -1;
    Hit_Box.left = -1;
    Hit_Box.height = -1;
    Hit_Box.width = -1;

    drawable->Hit_Box = Hit_Box;
    //#ifdef DEBUG
    //printf("New drawable is at the location %d\n", drawable_int );
    //#endif

    int aicontroller_int = bbAIControl_Pool_New(NEXT_AVAILABLE);

    //#ifdef DEBUG
    //printf("New AI Controller is at the location %d\n", aicontroller_int );
    //#endif
    drawable->AI_Controller = aicontroller_int;

    bbAIControl* aicontroller =  bbAIControl_Pool_Lookup(aicontroller_int);

    aicontroller->external_state  = AI_ARROW;
    aicontroller->internal_state = STATE_MOVING;
    aicontroller->SquareCoords = bbMapCoords_getSquareCoords(mc);


    aicontroller->drawables[0] = drawable_int;


    for(int i = 1; i<DRAWABLES_PER_AI; i++){
        aicontroller->drawables[i] = -1;

    }


    aicontroller->clock           = Current_Time;
    aicontroller->clock2          = 0;

    aicontroller->state_transition = 0;

    return aicontroller_int;
}

int AI_arrow_update(bbAIControl* aicontroller){

    int state = aicontroller->internal_state;
    int drawable_int = aicontroller->drawables[0];
    bbDrawable* drawable = bbDrawable_Pool_Lookup(drawable_int);


    //if (health <= 0) "become" DEAD, free AI Controller
    if (drawable->health <= 0){

        //arrow dies of lack of health?
    }



    int AI_drawable_int = aicontroller->drawables[0];
    bbDrawable* AI_drawable = bbDrawable_Pool_Lookup(AI_drawable_int);
    bbMapCoords AI_coords = AI_drawable->location;


    switch (state) {
        case STATE_IDLE:

            //arrow is idle?

            return NO_RETHUNK;

        case STATE_APPROACHING:

            //arrow is approaching a drawable?

            return NO_RETHUNK;

        case STATE_ATTACKING:

            //arrow hits drawable?

            return NO_RETHUNK;

        case STATE_MOVING:

            float speed = 8;

            float distance_to_target = bbMapCoords_getDistance(AI_drawable->location, AI_drawable->target_location);

            printf("distance to target = %f\n", distance_to_target);
            bbMapCoords new_location;

            if (distance_to_target < speed){
                new_location = AI_drawable->target_location;
            } else {
                //move toward target location;

                int delta_i = AI_drawable->target_location.i - AI_drawable->location.i;
                int delta_j = AI_drawable->target_location.j - AI_drawable->location.j;
                int delta_k = AI_drawable->target_location.k - AI_drawable->location.k;

                new_location.i = AI_drawable->location.i + (delta_i * speed) / distance_to_target;
                new_location.j = AI_drawable->location.j + (delta_j * speed) / distance_to_target;
                new_location.k = AI_drawable->location.k + (delta_k * speed) / distance_to_target;

            }

            //new_location.i = AI_coords.i + POINTS_PER_PIXEL;
            //new_location.j = AI_coords.j + POINTS_PER_PIXEL;
            //new_location.k = AI_coords.k;
            message_movement_new(AI_drawable_int , new_location);
            //is the drawable overlapping with a target drawable? Then set STATE_ATTACKING

            return NO_RETHUNK;
    }
    return NO_RETHUNK;
}

int AI_arrow_RPC (bbAIControl* aicontroller, bbMessage* message){

    return 0; //what does the return value signify?
}
