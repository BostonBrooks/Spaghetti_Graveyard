#define TEST_POOLS

#ifndef SYSTEM_INCLUDES
#define SYSTEM_INCLUDES
#include "../headers/system_includes.h"
#endif

#ifndef POOLS
#define POOLS
#include "../headers/pools.h"
#endif

typedef struct {
    int Pool_Self;
    int Pool_Prev;
    int Pool_Next;
    int Pool_In_Use;

    int data;
} bbNothing;

DEFINE_POOL(bbNothing, 4, 4)

int main(void){

    for (int i = 0; i<17; i++) {
        int nothing_int;
        nothing_int = bbNothing_Pool_New(NEXT_AVAILABLE);
        printf("nothing_int = %d\n", nothing_int);
        bbNothing *nothing = bbNothing_Pool_Lookup(nothing_int);
        printf("nothing->Pool_Self = %d\n", nothing->Pool_Self);
    }
}
