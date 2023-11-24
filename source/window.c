#include "../headers/window.h"

//-----------------------------INCLUDES----------------------------//

#include "../headers/system_includes.h"
#include "../headers/constants.h"
#include "../headers/media.h"


//-----------------------------CONSTANTS----------------------------//

//Constants may be found in constants.h

//-----------------------------STRUCURES------------------------------//

//-----------------------------GLOBALS----------------------------//

sfRenderWindow* window;


//-----------------------------FUNCTIONS--------------------------//

int Window_Init(void){

    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
    
    window = sfRenderWindow_create(mode, "Maths RPG", sfResize | sfClose, NULL);

    sfVector2i position;
    position.x = 0;
    position.y = 0;

    sfRenderWindow_setPosition(window, position);


    sfColor beige = COLOUR_BEIGE;
    
    sfRenderWindow_clear(window, beige);
    

}


int Display_Decal(void){

    sfRenderWindow_drawSprite(window, sfSprite_vtable[DECAL_INT],NULL);

}
