#ifndef BBNOTHING_H
#define BBNOTHING_H

//Old way of including headers
//#ifndef POOLS
//#define POOLS
//#include "../headers/pools_verbose.h"
//#endif

//New way of including headers:
#include "../headers/pools_verbose.h"

typedef struct {
    int Pool_Self;
    int Pool_Prev;
    int Pool_Next;
    int Pool_In_Use;

    int data;
} bbNothing;

//Function Declarations:
DECLARE_POOL_GLOBALS(bbNothing, 4, 4)


#endif
