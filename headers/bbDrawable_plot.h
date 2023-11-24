/**
 * @file
 *
 * @ingroup 
 * @brief Plot drawables to viewport
 */

#ifndef BBDRAWABLE_PLOT_H
#define BBDRAWABLE_PLOT_H

//-----------------------------INCLUDES----------------------------//

#include "../headers/constants.h"
#include "../headers/bbDrawable.h"

//-----------------------------GLOBALS----------------------------//

//Drawfunction types:
/*
#define DRAW_BASIC      0
#define DRAW_NULL       1
#define DRAW_REPEAT     2
#define DRAW_BALLOON    3
#define DRAW_SHADOW     4
*/

extern int (*bbDrawfunction_vtable[NUMBER_OF_DRAW_FUNCTIONS])(bbDrawable* tobedrawn, int i);
extern int Current_Time; //TODO this should be in a header/code file

extern sfCircleShape* Circle;

//-----------------------------CODE----------------------------//

/** Plot one bbDrawable to the viewport */
int bbDrawable_plot(bbDrawable* tobedrawn);

/** Plot one bbDrawable to the viewport given location in pool */
int bbDrawable_plot_int(int tobedrawn_int);

/** Plot all drawable sin pool wihtout regard to order */
int bbDrawable_plotPool(void);

/** Plot one animation from a drawable, do not advance the frame */
int basicdraw(bbDrawable* tobedrawn, int i);

/** Plot one animation from a drawable, do not advance the frame */
int nulldraw(bbDrawable* tobedrawn, int i);

/** Plot one frame from an animation and advance the animation*/
int repeatdraw(bbDrawable* tobedrawn, int i);

/** Plot a baloon, floating up and down */
int balloondraw(bbDrawable* tobedrawn, int i);

/** Plot the shadow under a unit */
int shadowdraw(bbDrawable* tobedrawn, int i);

/** Plot a tree to bbViewport_main, dont advance animation */
int treedraw(bbDrawable* tobedrawn, int i);

/** Plot a unit to  bbViewport_main and bbViewport_highlights */
int unitdraw(bbDrawable* tobedrawn, int i);

/** Initialise vtable of draw functions */
int bbDrawfunction_initAll();

#endif
