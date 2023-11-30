/**
 * @file
 *
 * @ingroup 
 * @brief A drawable is any object in the game that is drawn to the viewport 
 */

#ifndef BBDRAWABLE_H
#define BBDRAWABLE_H
//-----------------------------INCLUDES----------------------------//

#include "../headers/constants.h"
#include "../headers/geometry.h"
#include "../headers/pools.h"

#define NO_HEALTHBAR -1
//-----------------------------STRUCTS------------------------------//

/** A drawable is any object in the game that is drawn to the viewport */
 typedef struct {

/* Housekeeping Data: */
    bbSquareCoords SquareCoords;
    //what terrain square contains the drawable?
    //int i_Coord;
    //int j_Coord;
 
    int Pool_Self;
    int Pool_Prev;
    int Pool_Next;
    int Pool_In_Use;
    
    int Square_Prev;
    int Square_Next;
    
/* Cosmetic Data */

    bbMapCoords location;
    
    int health;
    int max_health;
    int display_health_until;
    int health_bar_height;
    int health_bar_width;
    int health_bar_length;
    
    int cosmetic_radius;

    int animation[ANIMATIONS_PER_DRAWABLE];
    int angle[ANIMATIONS_PER_DRAWABLE];
    int frame[ANIMATIONS_PER_DRAWABLE];
    int drawfunction[ANIMATIONS_PER_DRAWABLE];
    int start_time; //frame = ((current time - start time)/framerate)%frames

    int skin;
    int state;
    
/* Avoidance Data */
    
    float avoidance_radius;
    float mass;
    float speed;
    int shape;        //NO_POTENTIAL for no repulsion
    bbMapCoords preferred_next_location;
    bbMapCoords target_location;
    int target_drawable;

/* Interactive Data: */

    int onclick_function; //might want to implement a vtable or just not use this variable
    int AI_Controller;
    int Interactivity; //(-1 = none...0 = none, 1 = enemy, 2 = chest)
    bbIntRect Click_Box;

    int Ignore_Arrows; //-1 -> ignore arrows, 0-> dont ignore arrows
    bbIntRect Hit_Box;


    
     

} bbDrawable;

//-----------------------------CODE------------------------------//

DECLARE_POOL_GLOBALS(bbDrawable, 500, 51)
//DECLARE_POOL_GLOBALS(bbDrawable, DRAWABLE_POOL_LEVEL_1, DRAWABLE_POOL_LEVEL_2)
//Wy does the commented out line cause segfault in MSYS? Because you cannot allocate that much space in one go

/** return 1 if a is closer to the screen than b, 0 otherwise */
int bbDrawable_isCloser (bbDrawable* a, bbDrawable* b);

/** create a new drawable object (in the form of a barrel */
int bbDrawable_new(bbMapCoords MC);

int bbDrawable_new_tree(bbMapCoords MC);

/** drawable moves toward goal point */
int bbDrawable_movetowards(int drawable_int, bbMapCoords target_location);
int bbDrawable_movetowards_multiple(int drawable_int, bbMapCoords target_location);

/** This function calculates the endpoint of an arrow with a trajectory through the point mid_point */
int bbDrawable_set_passthrough(bbDrawable* drawable, bbMapCoords mid_point, float range);
#endif
