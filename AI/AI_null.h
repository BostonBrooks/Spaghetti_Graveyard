
#include "../headers/system_includes.h"
#include "../headers/constants.h"
#include "../headers/geometry.h"
#include "../headers/bbAIControl.h"
#include "../headers/bbMessage.h"
#include "../headers/bbDrawable.h"
#include "../headers/flags.h"
#include "../headers/bbMessage_constructors.h"

int AI_null_new(bbMapCoords mc){

    int drawable_int = bbDrawable_new(mc);
    bbDrawable* drawable = bbDrawable_Pool_Lookup(drawable_int);

    drawable->skin = -1;
    drawable->animation[0] = 16;
    drawable->angle[0] = 0;
    drawable->frame[0] = 0;
    drawable->drawfunction[0] = DRAW_BASIC;
    drawable->start_time = 0;
    //#ifdef DEBUG  
    //printf("New drawable is at the location %d\n", drawable_int );
    //#endif
    
    int aicontroller_int = bbAIControl_Pool_New(NEXT_AVAILABLE);

    bbAIControl* aicontroller =  bbAIControl_Pool_Lookup(aicontroller_int);
    
    
    aicontroller->SquareCoords = bbMapCoords_getSquareCoords(mc);
    

    aicontroller->drawables[0] = drawable_int;
    
    for(int i = 1; i<DRAWABLES_PER_AI; i++){
        aicontroller->drawables[i] = -1;
    
    }

    aicontroller->external_state  = AI_NULL;
    aicontroller->internal_state  = 0;
    
    aicontroller->clock           = 0;
    aicontroller->clock2          = 0;
    
    aicontroller->state_transition = 0;
    
    return aicontroller_int;
}

int AI_null_update(bbAIControl* aicontroller){


    return F_CONTINUE;

}

int AI_null_RPC (bbAIControl* aicontroller, bbMessage* message){

    return 0; //what does the return value signify?
}
