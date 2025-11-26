#include "../headers/bbMessage_functions.h"


//-----------------------------INCLUDES----------------------------//

#include "../headers/bbMessage.h"
#include "../headers/geometry.h"
#include "../headers/bbDrawable.h"
#include "../headers/constants.h"
#include "../headers/bbMessage_passing.h"
#include "../headers/bbSkin.h"
#include "../headers/bbDrawable_lists.h"
//-----------------------------GLOBALS----------------------------//

extern int Current_Time; //TODO Move to appropriate header file.

int (*bbMessage_type_vtable[NUMBER_OF_MESSAGE_TYPES])(bbMessage* message);


//-----------------------------CODE----------------------------//


int bbMessage_move_drawable(bbMessage* message){

    bbDrawable_setLocation(message->subject, message->mapcoords);
    return DELETE_MESSAGE;


}


int bbMessage_initTypes(){

    bbMessage_type_vtable[MESSAGE_MOVE] = bbMessage_move_drawable;
    
    return 0;
}
