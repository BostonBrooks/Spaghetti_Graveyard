/**
 * @file
 *
 * @ingroup 
 * @brief The mechanics of passing messages 
 */


#ifndef MESSAGE_PASSING_H
#define MESSAGE_PASSING_H

//-----------------------------INCLUDES----------------------------//

#include "../headers/constants.h"
#include "../headers/bbMessage.h"
#include "../headers/bbMessage_functions.h"

//-----------------------------GLOBALS----------------------------//

#define DELETE_MESSAGE    0
#define REUSE_MESSAGE     1

//-----------------------------CODE----------------------------//

extern int Current_Time; //TODO put in a new file. keep synched with other players

/** debug */
int print_message_details(int message_int);

/** debug */
int print_message_details_ALL();

/** Add message to queue */
int bbMessage_submit(int message_int);

/** Perform action specified by message */
int bbMessage_process(int message_int);

/** Perform all message queued, up to Current_Time */
int bbMessage_processAll();

#endif
