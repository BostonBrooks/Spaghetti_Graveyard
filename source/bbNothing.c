#include "../headers/bbNothing.h"

//Old way of including headers
#ifndef POOLS
#define POOLS
#include "../headers/pools_verbose.h"
#endif

//New way of including headers:
//#include "../headers/pools_verbose.h"

/* We dont have to rewrite this code
typedef struct {
    int Pool_Self;
    int Pool_Prev;
    int Pool_Next;
    int Pool_In_Use;

    int data;
} bbNothing;

*/

//Function Definitions:
DEFINE_POOL(bbNothing, 4, 4)