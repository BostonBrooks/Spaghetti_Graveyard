/**
 * @file
 *
 * @ingroup 
 * @brief Change the location of a drawable. Add to the appropriate terrain square
 */

#ifndef BBDRAWABLE_LISTS_H
#define BBDRAWABLE_LISTS_H

//-----------------------------INCLUDES----------------------------//

#include "../headers/constants.h"
#include "../headers/geometry.h"
#include "../headers/bbDrawable.h"
#include "../headers/media.h"
#include "../headers/bbMessage_functions.h"
#include "../headers/bbTerrainSquare.h"



//-----------------------------CODE------------------------------//

/** Change the location of drawable and add to list in appropriate terrain square */
int bbDrawable_setLocation(int drawable_int, bbMapCoords mc);

/** When creating a new drawable, use this to add to the appropriate terrain square */
int bbDrawable_addtoTS (int drawable_int);

#endif
