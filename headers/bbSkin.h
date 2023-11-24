/**
 * @file
 *
 * @ingroup
 * @brief each bbSkin contains INNER_STATES_PER_SKIN animations. These are templates the animations used by bbAIControl objects.
 */
 
#ifndef BBSKIN_H
#define BBSKIN_H
 
 
typedef struct {

    int animations_int [INNER_STATES_PER_SKIN][ANIMATIONS_PER_DRAWABLE];
    int drawfunctions_int [INNER_STATES_PER_SKIN][ANIMATIONS_PER_DRAWABLE];


} bbSkin;

extern bbSkin bbSkins [NUMBER_OF_SKINS];

//Later we will put animations in a dictionary,
//lookup animations from dictionary then add to skins.

int bbSkin_init();

#endif
