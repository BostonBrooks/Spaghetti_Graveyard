/**
 * @file
 *
 * @ingroup 
 * @brief This header file describes the actions of a Player AI, the player is prompted to move around the map by the data from input.h / input.c
 */

#include "../headers/system_includes.h"
#include "../headers/constants.h"
#include "../headers/geometry.h"
#include "../headers/bbAIControl.h"
#include "../headers/bbMessage.h"
#include "../headers/bbDrawable.h"
#include "../headers/input.h"

int PLAYER_new(bbMapCoords mc){

    int drawable_int = bbDrawable_new(mc);
    bbDrawable* drawable = bbDrawable_Pool_Lookup(drawable_int);

    //drawable->target_location.i = POINTS_PER_MAP/2;
    //drawable->target_location.j = POINTS_PER_MAP/2;

    drawable->skin = -1;
    // change drawable animation 
    drawable->animation[0] = 4;
    drawable->angle[0]     = 0;
    drawable->frame[0]     = 0;
    drawable->drawfunction[0]  = DRAW_UNIT;
    drawable->start_time       = 0;
    
    drawable->avoidance_radius = 32 * POINTS_PER_PIXEL;
    drawable->mass             = 1;
    drawable->speed            = 6;
    drawable->shape            = AVOIDANCE_CIRCLULAR;

    bbIntRect NULL_Hit_Box;
    NULL_Hit_Box.top      = -1;
    NULL_Hit_Box.left     = -1;
    NULL_Hit_Box.height   = -1;
    NULL_Hit_Box.width    = -1;

    drawable->onclick_function  = -1;
    drawable->AI_Controller     = -1;
    drawable->Interactivity     = -1;
    drawable->Click_Box         = NULL_Hit_Box;

    drawable->Ignore_Arrows     = -1;
    drawable->Hit_Box           = NULL_Hit_Box;

    drawable->health     = 100;
    drawable->max_health = 100;
    //#ifdef DEBUG  
    //printf("New drawable is at the location %d\n", drawable_int );
    //#endif
    
    int aicontroller_int = bbAIControl_Pool_New(NEXT_AVAILABLE);
    
    //#ifdef DEBUG  
    //printf("New AI Controller is at the location %d\n", aicontroller_int );
    //#endif
    drawable->AI_Controller = aicontroller_int;
    
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

int PLAYER_update(bbAIControl* aicontroller){

    
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
    bbMapCoords location = drawable->location;
    bbMapCoords target_location = drawable->target_location;

    bbDrawable_movetowards_multiple(drawable_int, target_location);



    return NO_RETHUNK;

}



int PLAYER_RPC (bbAIControl* aicontroller, bbMessage* message){

    return 0; //what does the return value signify?
}
