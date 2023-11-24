#include "../headers/bbMessage.h"
//-----------------------------INCLUDES----------------------------//

#include "../headers/pools.h"
#include "../headers/geometry.h"
#include "../headers/constants.h"

//-----------------------------GLOBALS------------------------------//


int bbMessage_head = -1;
int bbMessage_tail = -1;
//for the time being, we dont care what
// terrain square the message was sent to

//-----------------------------STRUCTS------------------------------//

//-----------------------------CODE------------------------------//
DEFINE_POOL(bbMessage, MESSAGE_POOL_LEVEL_1, MESSAGE_POOL_LEVEL_2)


int bbMessage_isAfter (bbMessage* a, bbMessage* b){ 
//return 1 if a is after b, 0 otherwise
    int time_a = a->Message_Time;
    int time_b = b->Message_Time;
    
    if (time_a > time_b) return 1;
    if (time_a == time_b) return 0;
    return -1;
}
