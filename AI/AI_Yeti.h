

#include "../headers/system_includes.h"
#include "../headers/constants.h"
#include "../headers/geometry.h"
#include "../headers/bbAIControl.h"
#include "../headers/bbMessage.h"
#include "../headers/bbDrawable.h"
#include "../headers/angles.h"

int AI_yeti_new(bbMapCoords mc){

    int drawable_int = bbDrawable_new(mc);
    bbDrawable* drawable = bbDrawable_Pool_Lookup(drawable_int);

    drawable->skin = -1;
    drawable->animation[0]     = 18;
    drawable->angle[0]         = rand() % 8;
    drawable->frame[0]         = 0;
    drawable->drawfunction[0]  = DRAW_REPEAT;
    drawable->start_time       = 0;
    
    drawable->avoidance_radius = 32 * POINTS_PER_PIXEL;
    drawable->mass             = 1;
    drawable->speed            = 4;
    drawable->shape            = AVOIDANCE_CIRCLULAR;  

    int aicontroller_int = bbAIControl_Pool_New(NEXT_AVAILABLE);
    

    
    bbAIControl* aicontroller =  bbAIControl_Pool_Lookup(aicontroller_int);
    
    
    aicontroller->SquareCoords = bbMapCoords_getSquareCoords(mc);
    

    aicontroller->drawables[0] = drawable_int;
    
    for(int i = 1; i<DRAWABLES_PER_AI; i++){
        aicontroller->drawables[i] = -1;
    
    }

    aicontroller->external_state  = AI_YETI;
    aicontroller->internal_state  = 0;
    
    aicontroller->clock           = 0;
    aicontroller->clock2          = 0;
    
    aicontroller->state_transition = 0;
    
    return aicontroller_int;
}

int AI_yeti_update(bbAIControl* aicontroller){

    int drawable_int = aicontroller->drawables[0];
    bbDrawable* drawable = bbDrawable_Pool_Lookup(drawable_int);
    
    int i = viewpoint.i - drawable->location.i;
    int j = viewpoint.j - drawable->location.j;
    
    int angle = angles_8(i, j);

    drawable->angle[0] = angle;
   
    bbMapCoords current_location = drawable->location;
    float radius = drawable->avoidance_radius; //drawable->radius;
    float speed = drawable->speed;
    bbMapCoords goal_point = viewpoint;
    bbMapCoords target_location = viewpoint;
    bbMapCoords new_location = viewpoint;
    bbMapCoords preferred_location = current_location;

    //find difference between current location and target location;
    
    float delta_i = target_location.i - current_location.i;
    float delta_j = target_location.j - current_location.j;
    //find distance to target location
    
    float distance = sqrt(delta_i * delta_i + delta_j * delta_j);
    
    if (distance > 64 * POINTS_PER_TILE) return NO_RETHUNK;
    //normalise difference by distance/speed
    
    //if (distance < POINTS_PER_TILE) return 0;
    
    delta_i = (delta_i * speed) / distance;
    delta_j = (delta_j * speed) / distance;
    
    preferred_location.i += delta_i;
    preferred_location.j += delta_j;
    
    drawable->preferred_next_location = preferred_location; 
    
    // use Nelder_Mead to calculate next point:
    new_location = nelder_mead (drawable_int);
    
    //Use gradient descent to calculate next point:
    //new_location = update_gradient (drawable_int);
    
    //update elevation of next point
    bbMapCoords_updateElevation(&new_location);
    
    //create movement message
    message_movement_new(drawable_int, new_location);

    return NO_RETHUNK;

}

int AI_yeti_RPC (bbAIControl* aicontroller, bbMessage* message){

    return 0; //what does the return value signify?
}
