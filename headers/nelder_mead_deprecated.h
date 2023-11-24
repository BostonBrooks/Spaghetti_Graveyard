/**
 * @file
 *
 * @ingroup 
 * @brief This header file contains code to minimise the potential of a drawable, in order to calculate next location
 */

#ifndef NELDER_MEAD_H
#define NELDER_MEAD_H

//-----------------------------INCLUDES----------------------------//

#include "../headers/geometry.h"
//-----------------------------CODE----------------------------//

/** minimise the potential of a drawable, in order to calculate next location */
bbMapCoords nelder_mead (int drawable_int);

#endif
