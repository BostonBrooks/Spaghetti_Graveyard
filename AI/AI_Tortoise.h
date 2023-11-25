
#include "../headers/system_includes.h"
#include "../headers/angles.h"
#include "../headers/constants.h"
#include "../headers/geometry.h"
#include "../headers/bbAIControl.h"
#include "../headers/bbMessage.h"
#include "../headers/bbDrawable.h"
#include "../headers/bbDrawable.h"
#include "../headers/sum_forces.h"

int AI_tortoise_new(bbMapCoords mc){

    //#ifdef DEBUG  
    //printf("Creating a tortoise AI object\n");
    //#endif
    
    int drawable_int = bbDrawable_new(mc);
    bbDrawable* drawable = bbDrawable_Pool_Lookup(drawable_int);

    drawable->skin = -1;
    drawable->animation[0] = 19;
    drawable->angle[0] = rand() % 32;
    drawable->frame[0] = 0;
    drawable->drawfunction[0] = DRAW_BASIC;
    drawable->start_time = 0;
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

    aicontroller->external_state  = AI_TORTOISE;
    aicontroller->internal_state  = 0;
    
    aicontroller->clock           = 0;
    aicontroller->clock2          = 0;
    
    aicontroller->state_transition = 0;
    
    return aicontroller_int;
}

int AI_tortoise_update(bbAIControl* aicontroller){

    //#ifdef DEBUG
    //printf("Updating a tortoise AI object\n");
    //#endif

    int drawable_int = aicontroller->drawables[0];
    bbDrawable* drawable = bbDrawable_Pool_Lookup(drawable_int);
    bbMapCoords location = drawable->location;
    bbMapCoords new_location = location;

    bbMapCoords target_location = viewpoint;

    int i = viewpoint.i - location.i;
    int j = viewpoint.j - location.j;

    int angle = angles_32(i, j);

    //#ifdef DEBUG
    //printf("Angle = %d\n", angle);
    //#endif

    drawable->angle[0] = angle;

    float delta_i = target_location.i - location.i;
    float delta_j = target_location.j - location.j;

    float distance = sqrt(delta_i * delta_i + delta_j * delta_j);

    float speed = 4;

    if (distance < speed){

        new_location.i = target_location.i;
        new_location.j = target_location.j;
    } else {

        delta_i = (delta_i * speed) / distance;
        delta_j = (delta_j * speed) / distance;

        new_location.i += delta_i;
        new_location.j += delta_j;

    }
    bbFloat3D forces = sum_forces_Nearby(drawable_int, location);

    //#ifdef DEBUG
    //printf("forces.i = %f, forces.j = %f]\n", forces.i, forces.j);
    //#endif

    new_location.i += forces.i;
    new_location.j += forces.j;

#ifdef DEBUG
    int movement_i = new_location.i - location.i;
    int movement_j = new_location.j - location.j;

    float movement_scalar = sqrt( movement_i * movement_i + movement_j * movement_j);
    float delta_scalar = sqrt( delta_i * delta_i + delta_j * delta_j);
    float forces_scalar = sqrt( forces.i * forces.i + forces.j * forces.j);

    if (movement_scalar > POINTS_PER_TILE) {
        printf("movement = %f, delta = %f, forces = %f\n", movement_scalar, delta_scalar, forces_scalar);
    sleep(60);
    }
#endif

    //update elevation of next point
    bbMapCoords_updateElevation(&new_location);

    message_movement_new(drawable_int, new_location);

    return NO_RETHUNK;

}

int AI_tortoise_RPC (bbAIControl* aicontroller, bbMessage* message){

    return 0; //what does the return value signify?
}
