//In potential_fields.c we have a variable "gap"
//forces are inversely proportional to 1/dist^2
//forces are capped to prevent glitchyness.
//forces are multiplied by the unit's mass.
//what about test point? for now, text_point = drawable_A->location

#ifndef SUM_FORCES_H
#define SUM_FORCES_H

//-----------------------------INCLUDES----------------------------//


#include "../headers/system_includes.h"
#include "../headers/constants.h"
#include "../headers/geometry.h"
#include "../headers/bbDrawable.h"
#include "../headers/bbTerrainSquare.h"

//-----------------------------GLOBALS----------------------------//

extern bbFloat3D (*force_shape_vtable[NUMBER_OF_AVOIDANCE_SHAPES])(int drawable_A_int, int drawable_B_int, bbMapCoords test_point);



int Sum_Forces_initShapes(void);

bbFloat3D sum_forces_Nearby(int, bbMapCoords);

#endif
