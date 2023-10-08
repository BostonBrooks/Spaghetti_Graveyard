//In potential_fields.c we have a variable "gap"
//forces are inversely proportional to 1/dist^2
//forces are capped to prevent glitchyness.
//forces are multiplied by the unit's mass.
//what about test point? for now, text_point = drawable_A->location
#define SUM_FORCES


//-----------------------------INCLUDES----------------------------//


#ifndef SYSTEM_INCLUDES
#define SYSTEM_INCLUDES
#include "../headers/system_includes.h"
#endif

#ifndef CONSTANTS
#define CONSTANTS
#include "../headers/constants.h"
#endif

#ifndef GEOMETRY
#define GEOMETRY
#include "../headers/geometry.h"
#endif

#ifndef BBDRAWABLE
#define BBDRAWABLE
#include "../headers/bbDrawable.h"
#endif

#ifndef BBTERRAINSQUARE
#define BBTERRAINSQUARE
#include "../headers/bbTerrainSquare.h"
#endif

//-----------------------------GLOBALS----------------------------//

float (*force_shape_vtable[NUMBER_OF_AVOIDANCE_SHAPES])(int drawable_A_int, int drawable_B_int, bbMapCoords test_point);


float force_untuned(float dist){

    return (1/(dist*dist));

}

float force (float distance){

    float magnitude = 1;
    float stiffness = 5;
    float offset = 0;

    float return_value = magnitude * force_untuned(distance * stiffness + offset);

    return(return_value);
}

bbFloat3 Circular_Force (int drawable_A_int, int drawable_B_int, bbMapCoords test_point) {

//drawable_A is the object being repelled
//drawable_B is the object doing the repelling,
//TODO multiply scalar force by drawable_B->mass
//test_point is the hypothetical position where drawable_A is located.

    bbDrawable* drawable_A = bbDrawable_Pool_Lookup(drawable_A_int);
    bbDrawable* drawable_B = bbDrawable_Pool_Lookup(drawable_B_int);

    int drawable_A_i = drawable_A->location.i;
    int drawable_A_j = drawable_A->location.j;
    float drawable_A_radius = drawable_A->avoidance_radius;


    int drawable_B_i = drawable_B->location.i;
    int drawable_B_j = drawable_B->location.j;
    float drawable_B_radius = drawable_B->avoidance_radius;

    //TODO what if avoidance_radius = -1

    int delta_i = test_point.i - drawable_B_i;
    int delta_j = test_point.j - drawable_B_j;

    float distance =  sqrt(delta_i * delta_i + delta_j*delta_j);
    float gap = distance - drawable_A_radius - drawable_B_radius;

    float scalar_force = force(gap);

    float normal_i = delta_i / distance;
    float normal_j = delta_j / distance;

    bbFloat3D vector_force;
    vector_force.i = scalar_force * normal_i;
    vector_force.j = scalar_force * normal_j;

    return vector_force;

}

bbFloat3 Square_Force (int drawable_A_int, int drawable_B_int, bbMapCoords test_point) {

    bbFloat3D vector_force;
    vector_force.i = 0;
    vector_force.j = 0;

    return vector_force;
}
bbFloat3 Line_Force (int drawable_A_int, int drawable_B_int, bbMapCoords test_point) {

    bbFloat3D vector_force;
    vector_force.i = 0;
    vector_force.j = 0;

    return vector_force;
}
bbFloat3 Rectangle_Force (int drawable_A_int, int drawable_B_int, bbMapCoords test_point) {

    bbFloat3D vector_force;
    vector_force.i = 0;
    vector_force.j = 0;

    return vector_force;
}

bbFloat3 Polygon_Force (int drawable_A_int, int drawable_B_int, bbMapCoords test_point) {

    bbFloat3D vector_force;
    vector_force.i = 0;
    vector_force.j = 0;

    return vector_force;
}

int Sum_Forces_initShapes(void){

    force_shape_vtable[AVOIDANCE_CIRCLULAR]    = Circular_Force;
    force_shape_vtable[AVOIDANCE_SQUARE]       = Square_Force;
    force_shape_vtable[AVOIDANCE_LINE]         = Line_Force;
    force_shape_vtable[AVOIDANCE_RECTANGLE]    = Rectangle_Force;
    force_shape_vtable[AVOIDANCE_POLYGON]      = Polygon_Force;

    return 0;

}

bbFloat3 sum_forces_per_square(int drawable_A_int, bbMapCoords test_point, int Square_i, int Square_j){

//drawable_A is the object being repelled, drawable_B is the object doing the repelling,
//test_point is the hypothetical position where drawable_A is located.

    bbTerrainSquare* TS = &bbTerrainSquare_grid[Square_i][Square_j];
    bbDrawable* drawable_A = bbDrawable_Pool_Lookup(drawable_A_int);
    bbDrawable* drawable_B;

    int drawable_B_int =  TS->bbDrawable_head;

    bbFloat3D output;
    output.i = 0;
    output.j = 0;
    output.k = 0;

    bbFloat3D temp;
    temp.i = 0;
    temp.j = 0;
    temp.k = 0;

    if(drawable_B_int == -1) return output; //if the square is empty, return 0

    drawable_B =  bbDrawable_Pool_Lookup(drawable_B_int);

    while(drawable_B_int != -1){

        drawable_B = bbDrawable_Pool_Lookup(drawable_B_int);

        if(drawable_B_int != drawable_A_int){

            if(drawable_B->shape != AVOIDANCE_NULL){

                temp = force_shape_vtable[drawable_B->shape]
                        (drawable_A_int, drawable_B_int, test_point);

                output.i += temp.i;
                output.j += temp.j;


            }


        }

        drawable_B_int = drawable_B->Square_Next;
    }

//printf("per square potential = %f\n", output);
    return output;


}

bbFloat3D sum_forces_Nearby(int drawable_A_int, bbMapCoords test_point){



    bbDrawable* drawable_A = bbDrawable_Pool_Lookup(drawable_A_int);

    bbSquareCoords SC = bbMapCoords_getSquareCoords(drawable_A->location);


    int i_min = SC.i-1;
    int j_min = SC.j-1;
    int i_max = SC.i+1;
    int j_max = SC.j+1;

    if (i_min < 0) i_min = 0;
    if (j_min < 0) j_min = 0;
    if (i_max >= SQUARES_PER_MAP ) i_max = SQUARES_PER_MAP;
    if (j_max >= SQUARES_PER_MAP ) j_max = SQUARES_PER_MAP;

    bbFloat3D output;
    output.i = 0;
    output.j = 0;
    output.k = 0;

    bbFloat3D temp;
    temp.i = 0;
    temp.j = 0;
    temp.k = 0;


    int Square_i, Square_j;
    for(Square_i = i_min; Square_i< i_max; Square_i++){
        for(Square_j = j_min; Square_j< j_max; Square_j++){

            temp = sum_forces_per_square(drawable_A_int, test_point, Square_i, Square_j);

            output.i += temp.i;
            output.j += temp.j;
        }

    }


    return output;


}