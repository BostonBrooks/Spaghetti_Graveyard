#include "../headers/bbDrawable.h"
//-----------------------------INCLUDES----------------------------//


#include "../headers/constants.h"
#include "../headers/geometry.h"
#include "../headers/pools.h"
#include "../headers/media.h"
#include "../headers/bbMessage_constructors.h"
#include <math.h>

//STUB #define NO_HEALTHBAR -1  // what even is this?


//-----------------------------CODE------------------------------//


#ifndef SUM_FORCES
#define SUM_FORCES
#include "../headers/sum_forces.h"
#endif

DEFINE_POOL(bbDrawable, 500, 51)
//DEFINE_POOL(bbDrawable, DRAWABLE_POOL_LEVEL_1, DRAWABLE_POOL_LEVEL_2)
//Wy does the commented out line cause segfault in MSYS? Because you cannot allocate that much space in one go

/** return 1 if a is closer to the screen than b, 0 otherwise */
int bbDrawable_isCloser (bbDrawable* a, bbDrawable* b){ 

    bbMapCoords mca = a->location;
    bbMapCoords mcb = b->location;
    
    return bbMapCoords_isCloser(mca, mcb);

}
/** Create a new drawable (a barrel) */
int bbDrawable_new(bbMapCoords MC){


    
    int drawable_int = bbDrawable_Pool_New(NEXT_AVAILABLE);


    assert(drawable_int >= 0);
    
    bbDrawable* drawable = bbDrawable_Pool_Lookup(drawable_int);

/* Cosmetic Data */

    
    drawable->location              = MC;
    drawable->health                = 5;
    drawable->max_health            = -1;
    drawable->display_health_until  = -1;
    drawable->health_bar_height     = -1;
    drawable->health_bar_width      = -1;
    drawable->health_bar_length     = -1;
    
    int cosmetic_radius             = -1;
    
    drawable->animation[0]          = 16;
    drawable->angle[0]              = 0;
    drawable->frame[0]              = 0;
    drawable->drawfunction[0]       = DRAW_BASIC;
     

    for (int i=1; i < ANIMATIONS_PER_DRAWABLE; i++){
   
   
       drawable->animation[i] = -1;
       drawable->angle[i] = -1;
       drawable->frame[i] = -1;
       drawable->drawfunction[i] = -1;
       
    }
    
    bbMapCoords NULL_Coords;
    
    NULL_Coords.i = -1;
    NULL_Coords.j = -1;
    NULL_Coords.k = -1;

/* Avoidance Data */
    

      
    drawable->avoidance_radius        = 20 * POINTS_PER_PIXEL;
    drawable->mass                    = -1;
    drawable->speed                   = -1;
    drawable->shape                   = AVOIDANCE_CIRCLULAR;
    drawable->preferred_next_location = NULL_Coords;
    drawable->target_location         = NULL_Coords;
    drawable->target_drawable         = -1;
    
/* Interactive Data: */

    
    bbIntRect NULL_Hit_Box;
    NULL_Hit_Box.top      = -1;
    NULL_Hit_Box.left     = -1;
    NULL_Hit_Box.height   = -1;
    NULL_Hit_Box.width    = -1;

    drawable->onclick_function  = -1;
    drawable->AI_Controller     = -1;
    drawable->Interactivity     = -1;
    drawable->Hit_Box           = NULL_Hit_Box;
    

/* Add to Terrain Sqaure */



    bbDrawable_addtoTS (drawable_int);

    return drawable_int;
}

int bbDrawable_new_tree(bbMapCoords MC){



    int drawable_int = bbDrawable_Pool_New(NEXT_AVAILABLE);


    assert(drawable_int >= 0);

    bbDrawable* drawable = bbDrawable_Pool_Lookup(drawable_int);

/* Cosmetic Data */




    drawable->location              = MC;
    drawable->health                = 5;
    drawable->max_health            = -1;
    drawable->display_health_until  = -1;
    drawable->health_bar_height     = -1;
    drawable->health_bar_width      = -1;
    drawable->health_bar_length     = -1;

    int cosmetic_radius             = -1;

    drawable->animation[0]          = 20;
    drawable->angle[0]              = rand()%52;
    drawable->frame[0]              = 0;
    drawable->drawfunction[0]       = DRAW_TREE;


    for (int i=1; i < ANIMATIONS_PER_DRAWABLE; i++){


        drawable->animation[i] = -1;
        drawable->angle[i] = -1;
        drawable->frame[i] = -1;
        drawable->drawfunction[i] = -1;

    }

    bbMapCoords NULL_Coords;

    NULL_Coords.i = -1;
    NULL_Coords.j = -1;
    NULL_Coords.k = -1;

/* Avoidance Data */


    drawable->avoidance_radius        = 2*POINTS_PER_TILE;
    drawable->mass                    = -1;
    drawable->speed                   = -1;
    drawable->shape                   = AVOIDANCE_CIRCLULAR;
    drawable->preferred_next_location = NULL_Coords;
    drawable->target_location         = NULL_Coords;
    drawable->target_drawable         = -1;

/* Interactive Data: */


    bbIntRect NULL_Hit_Box;
    NULL_Hit_Box.top      = -1;
    NULL_Hit_Box.left     = -1;
    NULL_Hit_Box.height   = -1;
    NULL_Hit_Box.width    = -1;

    drawable->onclick_function  = -1;
    drawable->AI_Controller     = -1;
    drawable->Interactivity     = -1;
    drawable->Hit_Box           = NULL_Hit_Box;


/* Add to Terrain Sqaure */


    bbDrawable_addtoTS (drawable_int);

    return drawable_int;
}


int angles_8_hack (float i, float j){ //STUB: Did this to avoid multiple definitions of the same function


    float x = i + j;
    float y = j - i;

    const float tan_A = -2.4142135623730;
    const float tan_B = -0.4142135623731;
    //tan_C = -tab_B
    //tan_D = -tan_A
    //tan E = tan_A
    //tan_F = tan_B
    //tan_G = -tan_B
    //tan_H = -tan_A

    if (x>0){ //vector (i, j) points to the right

        if (y < x * tan_A)  return 6;
        if (y < x * tan_B)  return 7;
        if (y < x * -tan_B) return 0;
        if (y < x * -tan_A) return 1;

        return 2;



    } else { //vector (i, j) points to the left

        if (y < -x * tan_A)  return 6;
        if (y < -x * tan_B)  return 5;
        if (y < -x * -tan_B) return 4;
        if (y < -x * -tan_A) return 3;

        return 2;

    }

}


int bbDrawable_movetowards(int drawable_int, bbMapCoords target_location){
    bbDrawable* drawable = bbDrawable_Pool_Lookup(drawable_int);
    bbMapCoords location = drawable->location;
    bbMapCoords new_location = location;

    int i = target_location.i - location.i;
    int j = target_location.j - location.j;

    int angle = angles_8_hack(i,j);
    drawable->angle[0] = angle;

    float distance = sqrt(i*i + j*j);
    float speed = 4;

    if(distance < speed){

        new_location.i = target_location.i;
        new_location.j = target_location.j;
    } else {
        float delta_i = (i * speed) / distance;
        float delta_j = (j * speed) / distance;

        new_location.i += delta_i;
        new_location.j += delta_j;
    }
    bbFloat3D forces = sum_forces_Nearby(drawable_int, location);

    new_location.i += forces.i;
    new_location.j += forces.j;

    bbMapCoords_updateElevation(&new_location);
    message_movement_new(drawable_int, new_location);

    return 0;
}

int bbDrawable_movetowards_multiple(int drawable_int, bbMapCoords target_location){

    bbDrawable* drawable = bbDrawable_Pool_Lookup(drawable_int);
    bbMapCoords location = drawable->location;
    bbMapCoords new_location = location;

    for (int dummy = 0; dummy < 4; dummy++){

        location = new_location;

        int i = target_location.i - new_location.i;
        int j = target_location.j - new_location.j;

        float distance = sqrt(i*i + j*j);
        float speed = 32;
        if(distance < speed){

            new_location.i = target_location.i;
            new_location.j = target_location.j;
        } else {
            float delta_i = (i * speed) / distance;
            float delta_j = (j * speed) / distance;

            new_location.i += delta_i;
            new_location.j += delta_j;
        }
        bbFloat3D forces = sum_forces_Nearby(drawable_int, location);

        new_location.i += forces.i;
        new_location.j += forces.j;
    }

    int i = target_location.i - new_location.i;
    int j = target_location.j - new_location.j;

    int angle = angles_8_hack(i,j);

    drawable->angle[0] = angle;
    bbMapCoords_updateElevation(&new_location);
    message_movement_new(drawable_int, new_location);

    return 0;
}

int bbDrawable_set_passthrough(bbDrawable* drawable, bbMapCoords mid_point, float range){

    bbMapCoords start_point = drawable->location;
    bbMapCoords end_point = start_point;

    float distance_to_target = bbMapCoords_getDistance(start_point, mid_point);

    if (distance_to_target > 0.0001) { //Not sure if this is good, but it prevents divide by zero

        int delta_i = mid_point.i - start_point.i;
        int delta_j = mid_point.j - start_point.j;
        int delta_k = mid_point.k - start_point.k;

        end_point.i += delta_i * (range / distance_to_target);
        end_point.j += delta_j * (range / distance_to_target);
        end_point.k += delta_k * (range / distance_to_target);

    }

    drawable->target_location = end_point;

    return 0;

}