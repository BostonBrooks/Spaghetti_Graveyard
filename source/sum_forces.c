//In potential_fields.c we have a variable "gap"
//forces are inversely proportional to 1/dist^2
//forces are capped to prevent glitchyness.
//forces are multiplied by the unit's mass.
//what about test point? for now, text_point = drawable_A->location

#include "../headers/sum_forces.h"

//-----------------------------INCLUDES----------------------------//


#include "../headers/system_includes.h"
#include "../headers/constants.h"
#include "../headers/geometry.h"
#include "../headers/bbDrawable.h"
#include "../headers/bbTerrainSquare.h"
#include "../headers/bbPrintf.h"
//-----------------------------GLOBALS----------------------------//

bbFloat3D (*force_shape_vtable[NUMBER_OF_AVOIDANCE_SHAPES])(int drawable_A_int, int drawable_B_int, bbMapCoords test_point);


float force_untuned(float x){


    return -x / (1+fabs(x)) + 1;



}


float force (float distance){

    float magnitude = 16;
    float stiffness = 3;
    float offset = 0;

    float return_value = magnitude * force_untuned(distance * stiffness + offset);

    return(return_value);
}

bbFloat3D Circular_Force (int drawable_A_int, int drawable_B_int, bbMapCoords test_point) {

//drawable_A is the object being repelled
//drawable_B is the object doing the repelling,
//STUB: multiply scalar force by drawable_B->mass
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

    int delta_i = test_point.i - drawable_B_i; //Use long to prevent overflow
    int delta_j = test_point.j - drawable_B_j;

    float distance = bbMapCoords_getDistance(test_point, drawable_B->location);

    bbFloat3D vector_force;
    if (distance < 8){ //TODO fixes glitchiness but there shouldnt be no force when drawables are too close together.

        vector_force.i = 0;
        vector_force.j = 0;

        return vector_force;

    }

    float gap = distance - drawable_A_radius - drawable_B_radius;

    float scalar_force = force(gap);

    float normal_i = delta_i / distance;
    float normal_j = delta_j / distance;


    vector_force.i = scalar_force * normal_i;
    vector_force.j = scalar_force * normal_j;

    float debug_force = sqrt(vector_force.i * vector_force.i + vector_force.j * vector_force.j);

    if (debug_force > POINTS_PER_SQUARE){
        bbDebug("distance = %f\n", distance);
    }
    return vector_force;

}

bbFloat3D Square_Force (int drawable_A_int, int drawable_B_int, bbMapCoords test_point) {

    bbFloat3D vector_force;
    vector_force.i = 0;
    vector_force.j = 0;

    return vector_force;
}
bbFloat3D Line_Force (int drawable_A_int, int drawable_B_int, bbMapCoords test_point) {

    bbFloat3D vector_force;
    vector_force.i = 0;
    vector_force.j = 0;

    return vector_force;
}
bbFloat3D Rectangle_Force (int drawable_A_int, int drawable_B_int, bbMapCoords test_point) {

    bbFloat3D vector_force;
    vector_force.i = 0;
    vector_force.j = 0;

    return vector_force;
}

bbFloat3D Polygon_Force (int drawable_A_int, int drawable_B_int, bbMapCoords test_point) {

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

bbFloat3D sum_forces_per_square(int drawable_A_int, bbMapCoords test_point, int Square_i, int Square_j){

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

                float debug_force = sqrt(temp.i * temp.i + temp.j * temp.j);

                assert(debug_force < POINTS_PER_SQUARE);

            }


        }

        drawable_B_int = drawable_B->Square_Next;
    }




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