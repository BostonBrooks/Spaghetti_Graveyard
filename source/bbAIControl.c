#include "../headers/bbAIControl.h"

//-----------------------------INCLUDES----------------------------//

//STUB: May want to move the following into .h file
#include "../headers/constants.h"
#include "../headers/geometry.h"
#include "../headers/pools.h"
#include "../headers/bbDrawable.h"
#include "../headers/bbAIControl_init.h"

//-----------------------------CODE------------------------------//

DEFINE_POOL(bbAIControl, AICONTROLLER_POOL_LEVEL_1, AICONTROLLER_POOL_LEVEL_2);


// What happens when you have an extern of something in the same file as the non-extern?
// Nothing happens, all good
extern int (*bbAI_update_vtable[NUMBER_OF_EXTERNAL_STATES])(bbAIControl* aicontroller);


int bbAIControl_update(bbAIControl* aicontroller){
    
    int type;
    
    int rethunk = RETHUNK;

    
    
    while (rethunk == RETHUNK){
    
        type = aicontroller->external_state;

        rethunk = bbAI_update_vtable[type](aicontroller);
        if (rethunk == KILL_AI){
            return KILL_AI;
        }

    }

    return 0;
}

int bbAIControl_update_int(int aicontroller_int){

    bbAIControl* aicontroller = bbAIControl_Pool_Lookup(aicontroller_int);
    
    int type;
    
    int rethunk = RETHUNK;
    
    while (rethunk == RETHUNK){
    
        type = aicontroller->external_state;
        rethunk = bbAI_update_vtable[type](aicontroller);
        if (rethunk == KILL_AI){
            return KILL_AI;
        }
    }

    return 0;
}

int bbAIControl_updatePool(void){

    int tobeupdated_int = bbAIControl_Pool_In_Use_Head;
    int previous_int;
    int killflag;
    
    if ( tobeupdated_int == -1) return 0;
    

    
    
    while (tobeupdated_int != -1){
    

        bbAIControl* tobeupdated = bbAIControl_Pool_Lookup(tobeupdated_int);
        killflag = bbAIControl_update(tobeupdated);
        previous_int = tobeupdated_int;
        tobeupdated_int = tobeupdated->Pool_Next;
        if(killflag == KILL_AI) {
            //Cleanup orphaned drawables;
            for (int i = 0; i<DRAWABLES_PER_AI; i++){
                int drawable_int = tobeupdated->drawables[i];
                if (drawable_int >= 0) {
                    bbDrawable *drawable = bbDrawable_Pool_Lookup(drawable_int);
                    drawable->AI_Controller = -1;
                }
            }
            //Delete AI Controller
            bbAIControl_Pool_Delete(previous_int);



        }


    }
    return 0;
}
