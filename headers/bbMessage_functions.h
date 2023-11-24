/**
 * @file
 *
 * @ingroup 
 * @brief Types of message and what their effects are.
 */

#ifndef BBMESSAGE_FUNCTIONS_H
#define BBMESSAGE_FUNCTIONS_H

//-----------------------------INCLUDES----------------------------//


#include "../headers/bbMessage.h"
#include "../headers/constants.h"


//-----------------------------GLOBALS----------------------------//

/** vtable containing message types */
extern int (*bbMessage_type_vtable[NUMBER_OF_MESSAGE_TYPES])(bbMessage* message);


//-----------------------------CODE----------------------------//


//probably will not call this function directly:
/** when this message is processed, it changes the location of a drawable */
int bbMessage_move_drawable(bbMessage* message);

/** populate vtable of message types */
int bbMessage_initTypes();

#endif
