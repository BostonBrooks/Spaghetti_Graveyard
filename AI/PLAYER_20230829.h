/**
 * @file
 *
 * @ingroup 
 * @brief This header file describes the actions of a Player AI, the player is prompted to move around the map by the data from input.h / input.c
 */
 
 //Declare includes. note extra "../"
 //this is because we are in "~/source/AI"
 //and not "~/source" or "~/headers"
 
#ifndef SYSTEM_INCLUDES
#define SYSTEM_INCLUDES
#include "../../headers/system_includes.h"
#endif

#ifndef CONSTANTS
#define CONSTANTS
#include "../../headers/constants.h"
#endif

#ifndef GEOMETRY
#define GEOMETRY
#include "../../headers/geometry.h"
#endif

#ifndef BBAICONTROL
#define BBAICONTROL
#include "../../headers/bbAIControl.h"
#endif

#ifndef BBMESSAGE
#define BBMESSAGE
#include "../../headers/bbMessage.h"
#endif

#ifndef BBDRAWABLE
#define BBDRAWABLE
#include "../../headers/bbDrawable.h"
#endif

#ifndef INPUT
#define INPUT
#include "../../headers/input.h"
#endif

int PLAYER_20230829_new(bbMapCoords mc){

    //#ifdef DEBUG  
    //printf("Creating a null AI object\n");
    //#endif
    
    int drawable_int = bbDrawable_new(mc);
    bbDrawable* drawable = bbDrawable_Pool_Lookup(drawable_int);
    
    
    // change drawable animation 
    drawable->animation[0] = 4;
    drawable->angle[0]     = 0;
    drawable->frame[0]     = 0;
    drawable->drawfunction[0]  = DRAW_BASIC;
    drawable->start_time       = 0;
    
    drawable->avoidance_radius = 32 * POINTS_PER_PIXEL;
    drawable->mass             = 1;
    drawable->speed            = 6;
    drawable->shape            = AVOIDANCE_CIRCLULAR;  
    //#ifdef DEBUG  
    //printf("New drawable is at the location %d\n", drawable_int );
    //#endif
    
    int aicontroller_int = bbAIControl_Pool_New(NEXT_AVAILABLE);
    
    //#ifdef DEBUG  
    //printf("New AI Controller is at the location %d\n", aicontroller_int );
    //#endif
    
    
    bbAIControl* aicontroller =  bbAIControl_Pool_Lookup(aicontroller_int);
    
    
    aicontroller->SquareCoords = bbMapCoords_getSquareCoords(mc);
    

    aicontroller->drawables[0] = drawable_int;
    
    for(int i = 1; i<DRAWABLES_PER_AI; i++){
        aicontroller->drawables[i] = -1;
    
    }

    aicontroller->external_state  = PLAYER_20230829;
    aicontroller->internal_state  = 0;
    
    aicontroller->clock           = 0;
    aicontroller->clock2          = 0;
    
    aicontroller->state_transition = 0;
    
    return aicontroller_int;
}

int PLAYER_20230829_update(bbAIControl* aicontroller){

    #ifdef DEBUG  
    printf("Updating a Player AI object\n");
    #endif
    
    int drawable_int = aicontroller->drawables[0];
    bbDrawable* drawable = bbDrawable_Pool_Lookup(drawable_int);
    
    //test movement    
    if (left_button_down == 1){
    
    //set goal point to mouse position
    
        drawable->target_location = mouse_map_position;
        drawable->location = mouse_map_position;
        
        left_button_down = 0;
        
        return NO_RETHUNK;
        
    }
    

    //if right mouse button down
    if (right_button_down == 1){
    
    //set goal point to mouse position
    
        drawable->target_location = mouse_map_position;
        
    }
    
    /////move towards goal point//////
    bbMapCoords current_location = drawable->location;
    bbMapCoords target_location = drawable->target_location;
    
    
    
    //find difference between current location and target location;
    float delta_i = target_location.i - current_location.i;
    float delta_j = target_location.j - current_location.j;
    
    //find distance to target location
    float distance = sqrt(delta_i * delta_i + delta_j * delta_j);
    
    //normalise difference by distance/speed
    
    float speed = drawable->speed;
    
    if (distance < speed){
    
        drawable->preferred_next_location = target_location;
    
    } else {
    
    
        delta_i = (delta_i * speed) / distance;
        delta_j = (delta_j * speed) / distance;
    
        bbMapCoords preferred_location = current_location;
    
        preferred_location.i += delta_i;
        preferred_location.j += delta_j;    
    
    
    
        drawable->preferred_next_location = preferred_location;
    
    }
    
    // use Nelder_Mead to calculate next point:
    bbMapCoords new_location = nelder_mead (drawable_int);
    
    //update elevation of next point
    bbMapCoords_updateElevation(&new_location);
    
    //create movement message
    message_movement_new(drawable_int, new_location);
    
    //TODO set angle (ATM there is only 1 angle)

    return NO_RETHUNK;

}

int PLAYER_20230829_RPC (bbAIControl* aicontroller, bbMessage* message){

    return 0; //what does the return value signify?
}
