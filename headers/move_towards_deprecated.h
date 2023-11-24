/**
 * @file
 *
 * @ingroup 
 * @brief Moves a map coords ubject towards a goal point with no local avoidance
 */

#ifndef MOVE_TOWARDS_H
#define MOVE_TOWARDS_H
//-----------------------------INCLUDES----------------------------//


#include "../headers/geometry.h"

/** Moves a map coords ubject towards a goal point with no local avoidance */
int bbMapCoords_move_toward(bbMapCoords* subject, bbMapCoords object, float distance);

#endif
