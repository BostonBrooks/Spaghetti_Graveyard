#define WINDOW

//-----------------------------INCLUDES----------------------------//

#ifndef SYSTEM_INCLUDES
#define SYSTEM_INCLUDES
#include "../headers/system_includes.h"
#endif

#ifndef CONSTANTS
#define CONSTANTS
#include "../headers/constants.h"
#endif

#ifndef MEDIA
#define MEDIA
#include "../headers/media.h"
#endif

//-----------------------------CONSTANTS----------------------------//

//Constants may be found in constants.h

//-----------------------------STRUCURES------------------------------//

//-----------------------------GLOBALS----------------------------//

sfRenderWindow* window;


//-----------------------------FUNCTIONS--------------------------//

int Window_Init(void){

    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
    
    window = sfRenderWindow_create(mode, "Maths RPG", sfResize | sfClose, NULL);
    
    //assert(window != 0);
    sfRenderWindow_setFramerateLimit(window, 0);
    
    sfColor beige = COLOUR_BEIGE;
    
    sfRenderWindow_clear(window, beige);
    

}


int Display_Decal(void){

    sfRenderWindow_drawSprite(window, sfSprite_vtable[DECAL_INT],NULL);

}
