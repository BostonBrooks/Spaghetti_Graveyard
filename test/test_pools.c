#define TEST_POOLS

#ifndef POOLS
#define POOLS
#include "../headers/pools_verbose.h"
#endif

#ifndef ALL_INCLUDES
#define ALL_INCLUDES
#include "../headers/all_includes.h"
#endif

int Current_Time = 0;

typedef struct {
    int Pool_Self;
    int Pool_Prev;
    int Pool_Next;
    int Pool_In_Use;

    int data;
} bbNothing;

DEFINE_POOL(bbNothing, 4, 4)

int main(void){
    int nothing_int;
    nothing_int = bbNothing_Pool_New(NEXT_AVAILABLE);
    printf("nothing_int = %d\n", nothing_int);
    bbNothing *nothing = bbNothing_Pool_Lookup(nothing_int);
    printf("nothing->Pool_Self = %d\n", nothing->Pool_Self);

    int drawable_int;
    drawable_int = bbDrawable_Pool_New(NEXT_AVAILABLE);
    printf("drawable_int = %d\n", drawable_int);
    bbDrawable *drawable = bbDrawable_Pool_Lookup(drawable_int);
    printf("drawable->Pool_Self = %d\n", drawable->Pool_Self);

}
