#include "../headers/bbAIControl.h"

//-----------------------------INCLUDES----------------------------//

//STUB: May want to move the following into .h file
#include "../headers/constants.h"
#include "../headers/geometry.h"
#include "../headers/pools.h"
#include "../headers/bbDrawable.h"
#include "../headers/bbAIControl_init.h"
#include "../headers/flags.h"

//-----------------------------CODE------------------------------//

DEFINE_POOL(bbAIControl, AICONTROLLER_POOL_LEVEL_1, AICONTROLLER_POOL_LEVEL_2);
int bbDrawable_removefromTS (int drawable_int);

// What happens when you have an extern of something in the same file as the non-extern?
// Nothing happens, all good
extern int (*bbAI_update_vtable[NUMBER_OF_EXTERNAL_STATES])(bbAIControl* aicontroller);


int bbAIControl_update(bbAIControl* aicontroller){
    
    int type;
    
    int flag = F_REPEAT;

    
    
    while (flag == F_REPEAT){
    
        type = aicontroller->external_state;

		flag = bbAI_update_vtable[type](aicontroller);
        if (flag == F_DELETE){
            return F_DELETE;
        }
        if (flag == F_ANNIHILATE){
            return F_ANNIHILATE;
        }

    }

    return 0;
}

int bbAIControl_update_int(int aicontroller_int){

    bbAIControl* aicontroller = bbAIControl_Pool_Lookup(aicontroller_int);
    
    int type;
    
    int flag = F_REPEAT;
    
    while (flag == F_REPEAT){
    
        type = aicontroller->external_state;
		flag = bbAI_update_vtable[type](aicontroller);
        if (flag == F_DELETE){
            return F_DELETE;
        }
        if (flag == F_ANNIHILATE){
            return F_ANNIHILATE;
        }
    }

    return 0;
}

int bbAIControl_updatePool(void){

    int tobeupdated_int = bbAIControl_Pool_In_Use_Head;
    int previous_int;
    int flag;
    
    if ( tobeupdated_int == -1) return 0;
    

    
    
    while (tobeupdated_int != -1){
    

        bbAIControl* tobeupdated = bbAIControl_Pool_Lookup(tobeupdated_int);
        flag = bbAIControl_update(tobeupdated);
        previous_int = tobeupdated_int;
        tobeupdated_int = tobeupdated->Pool_Next;
        if(flag == F_DELETE) {
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



        } else if (flag == F_ANNIHILATE){    //TODO delete drawables in a message


                //Cleanup orphaned drawables;
                for (int i = 0; i<DRAWABLES_PER_AI; i++){
                    int drawable_int = tobeupdated->drawables[i];
                    if (drawable_int >= 0) {
                        //remove drawable from lists and delete
                        bbDrawable_removefromTS (drawable_int);
                        bbDrawable_Pool_Delete(drawable_int);
                    }
                }
                //Delete AI Controller
                bbAIControl_Pool_Delete(previous_int);
        }


    }
    return 0;
}
