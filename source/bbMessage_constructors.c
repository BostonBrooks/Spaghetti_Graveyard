#include "../headers/bbMessage_constructors.h"



//-----------------------------INCLUDES----------------------------//

#include "../headers/bbMessage.h"
#include "../headers/bbMessage_passing.h"
#include "../headers/constants.h"
#include "../headers/bbMessage_functions.h"

//-----------------------------CODE------------------------------//

int message_movement_new(int drawable_int, bbMapCoords mc){

    int message_int = bbMessage_Pool_New(NEXT_AVAILABLE);
    bbMessage* message =  bbMessage_Pool_Lookup(message_int);
    message->Message_Time = 1;
    message->type = MESSAGE_MOVE;
    message->subject = drawable_int;
    message->mapcoords = mc;
    bbMessage_submit(message_int);
    
}
