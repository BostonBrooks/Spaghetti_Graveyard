
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

int AI_cow_new(bbMapCoords mc){

    //#ifdef DEBUG
    //printf("Creating a tortoise AI object\n");
    //#endif

    int drawable_int = bbDrawable_new(mc);
    bbDrawable* drawable = bbDrawable_Pool_Lookup(drawable_int);

    drawable->skin = 0;
    drawable->state = STATE_IDLE;
    drawable->animation[0] = ANIMATION_SKIN;
    drawable->angle[0] = rand() % 8;
    drawable->frame[0] = 0;
    drawable->drawfunction[0] = DRAW_SKIN;
    drawable->start_time = 0;
    drawable->avoidance_radius = POINTS_PER_TILE;
    //#ifdef DEBUG
    //printf("New drawable is at the location %d\n", drawable_int );
    //#endif

    int aicontroller_int = bbAIControl_Pool_New(NEXT_AVAILABLE);

    //#ifdef DEBUG
    //printf("New AI Controller is at the location %d\n", aicontroller_int );
    //#endif
    drawable->AI_Controller = aicontroller_int;

    bbAIControl* aicontroller =  bbAIControl_Pool_Lookup(aicontroller_int);

    aicontroller->external_state  = AI_COW;
    aicontroller->internal_state = STATE_IDLE;
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

int AI_cow_update(bbAIControl* aicontroller){

    int state = aicontroller->internal_state;
    int drawable_int = aicontroller->drawables[0];
    bbDrawable* drawable = bbDrawable_Pool_Lookup(drawable_int);


    //if (health <= 0) "become" DEAD, free AI Controller
    if (drawable->health <= 0){
        drawable->state = STATE_DEAD;

        for(int i = 0; i < ANIMATIONS_PER_DRAWABLE; i++){
            drawable->frame[i] = 0;
        }

        return KILL_AI;
    }

    bbAIControl* player_AI = bbAIControl_Pool_Lookup(player_int);

    int player_drawable_int = player_AI->drawables[0];
    bbDrawable* player_drawable = bbDrawable_Pool_Lookup(player_drawable_int);
    bbMapCoords player_coords = player_drawable->location;

    int AI_drawable_int = aicontroller->drawables[0];
    bbDrawable* AI_drawable = bbDrawable_Pool_Lookup(AI_drawable_int);
    bbMapCoords AI_coords = AI_drawable->location;

    float distance = bbMapCoords_getDistance(player_coords, AI_coords);

    switch (state) {
        case STATE_IDLE:
            if (aicontroller->state_transition == 1){
                //update drawable state
                //set clock to zero
                //set state transition to zero

                drawable->state = STATE_IDLE;

                for(int i = 0; i < ANIMATIONS_PER_DRAWABLE; i++){
                    drawable->frame[i] = 0;
                }

                aicontroller->clock = Current_Time;
                aicontroller->state_transition = 0;
            }
            //if player within range, "become" APPROACHING
            //set target
            //set state to approaching
            //set state_transition
            //return RETHUNK


            if (distance < 25 * POINTS_PER_TILE) {
                aicontroller->internal_state = STATE_APPROACHING;
                AI_drawable->target_drawable = player_drawable->Pool_Self;
                aicontroller->state_transition = 1;
                return RETHUNK;
            }

            return NO_RETHUNK;

        case STATE_APPROACHING:

            if (aicontroller->state_transition == 1){
                //update drawable state
                //set clock to zero
                //set state_transition to zero
                drawable->state = STATE_APPROACHING;

                for(int i = 0; i < ANIMATIONS_PER_DRAWABLE; i++){
                    drawable->frame[i] = 0;
                }

                aicontroller->clock = Current_Time;
                aicontroller->state_transition = 0;
            }
            //if player out of view, "become" IDLE
            if (distance > 25 * POINTS_PER_TILE){
                aicontroller->internal_state = STATE_IDLE;
                aicontroller->state_transition = 1;
                return RETHUNK;

            }

            //else if player within range, "become" ATTACKING

            if (distance < 5*POINTS_PER_TILE) {
                aicontroller->internal_state = STATE_ATTACKING;
                aicontroller->attack_centre = player_coords;
                aicontroller->state_transition = 1;
                return RETHUNK;

            }

            //else move towards player
            bbDrawable_movetowards(AI_drawable_int, player_coords);
            return NO_RETHUNK;

        case STATE_ATTACKING:
            if (aicontroller->state_transition == 1){
                //update drawable state
                //set clock to zero
                //set state_transition to zero
                drawable->state = STATE_ATTACKING;

                for(int i = 0; i < ANIMATIONS_PER_DRAWABLE; i++){
                    drawable->frame[i] = 0;
                }

                aicontroller->clock = Current_Time;
                aicontroller->state_transition = 0;
            }

            if (Current_Time == aicontroller->clock + 160){
                //Is the player within the effected area?
                float dist = bbMapCoords_getDistance(player_coords, aicontroller->attack_centre);
                if (dist < POINTS_PER_TILE * 2) {
                    damage_player(5);
                    printf("You got hit\n");
                }
            }

            if (Current_Time > aicontroller->clock + 304) {
                aicontroller->internal_state = STATE_IDLE;
                aicontroller->state_transition = 1;
                return RETHUNK;

            }
            //if player within range and Current_Time = clock + ?
            //damage player
            //if Current_Time >= clock + ??
            //"become" IDLE

            //else move towards player
            return NO_RETHUNK;
    }
    return NO_RETHUNK;
}

int AI_cow_RPC (bbAIControl* aicontroller, bbMessage* message){

    return 0; //what does the return value signify?
}