#define BBNOTHING

#ifndef POOLS
#define POOLS
#include "../headers/pools_verbose.h"
#endif

typedef struct {
    int Pool_Self;
    int Pool_Prev;
    int Pool_Next;
    int Pool_In_Use;

    int data;
} bbNothing;

DEFINE_POOL(bbNothing, 4, 4)