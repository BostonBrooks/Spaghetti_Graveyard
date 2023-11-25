/**
 * @file
 *
 * @ingroup 
 * @brief Input key presses and mouse clicks
 */
 
#include "../headers/input.h"

int heal_player(int x);
//-----------------------------INCLUDES----------------------------//


#include "../headers/prompt.h"
#include "../headers/system_includes.h"
#include "../headers/bbDrawable.h"
#include "../headers/geometry.h"
#include "../headers/window.h"
#include "../headers/bbAIControl_init.h"

//-----------------------------GLOBALS----------------------------//

bbScreenCoords mouse_screen_position;
extern int player_int;

bbScreenCoords mouse_viewport_position;

bbMapCoords mouse_map_position;

int right_button_down;
//if right button is down, player AI will set goal point to mouse_map_position
int left_button_down;
//if button is clicked the player AI will attack the ground at that point

//int bbTerrainSquare_onclick_visible(bbScreenCoords SC, int mousebutton);

//-----------------------PLACEHOLDER FUNCTIONS--------------------//

/** This function will enable the user to left or right click widgets */
int process_click_widgets(int x, int y, int right_click){


    return 0;
    
}

/** This function will eventually enable the user to left click monsters */
int process_click_drawables(int x, int y, int right_click);
/*int process_click_drawables(int x, int y, int right_click){

    if (right_click == 0){
        heal_player(-50);
        printf("You are being healed\n");
        return 1;
    }
    return 0;
}
*/
//-----------------------------FUNCTIONS--------------------------//

int process_key_event(sfEvent);

int input_process(void){

    sfEvent event;
    //update mouse screen position;
    sfVector2i position = sfMouse_getPosition(window);
    
    mouse_screen_position.x = position.x;
    mouse_screen_position.y = position.y;
    
    mouse_viewport_position.x = position.x - VIEWPORT_LEFT ;
    mouse_viewport_position.y = position.y - VIEWPORT_TOP;
    
    bbMapCoords test_coords = bbScreenCoords_getMapCoords(mouse_viewport_position);
    
    if (test_coords.i != -1 && test_coords.j != -1 && test_coords.k != -1){
    
        mouse_map_position = test_coords;
    }
    
    
    
    
    //if the result of bbScreenCoords_getMapCoords() is valid,
    // update mouse_map_position
    
//TODO as of now there is no clicking and dragging widgets
//TODO as of now it's not possible to left click the ground (for attack ground feature)
   while(sfRenderWindow_pollEvent(window, &event)){
   
   
       if (event.type == sfEvtClosed)
       {
           exit(1);
       
       //if key event
       } else if (event.type == sfEvtKeyPressed){
           //pass key to prompt
           process_key_event(event);

       //if mouse button down
       } else if (event.type == sfEvtMouseButtonPressed){
           //if left button down
           if (event.mouseButton.button == sfMouseLeft){
               //printf("you left clicked\n");
               //check if a widget is being clicked & process
               if (process_click_widgets( //This is an example of Guard Clause
                   mouse_screen_position.x,
                   mouse_screen_position.y,
                   0) == 1){ //The third argument is a flag to tell process_click_widgets that the widget is being left clicked
                   //do nothing
                   
               //or check if a monster is being clicked & process
               } else if (process_click_drawables(
                   mouse_viewport_position.x,
                   mouse_viewport_position.y,
                   0) == 1){
                   printf("You left clicked a drawable\n");
                   //The third argument is a flag to tell process_click_drawables that the drawable is being left clicked
               } else {

                   bbAIControl* player_AI = bbAIControl_Pool_Lookup(player_int);

                   int player_drawable_int = player_AI->drawables[0];
                   bbDrawable* player_drawable = bbDrawable_Pool_Lookup(player_drawable_int);
                   bbMapCoords player_coords = player_drawable->location;

                   player_coords.k += POINTS_PER_TILE * 4;  //STUB: should be based on unit height

                   int arrow_AI_int = bbAI_constructor_vtable[AI_ARROW](player_coords);
                   bbAIControl* arrow_AI = bbAIControl_Pool_Lookup(arrow_AI_int);
                   int arrow_drawable_int = arrow_AI->drawables[0];
                   bbDrawable* arrow_drawable = bbDrawable_Pool_Lookup(arrow_drawable_int);
                   bbMapCoords target_location = bbScreenCoords_getMapCoords_k_fixed (mouse_viewport_position, player_coords.k);

                   bbDrawable_set_passthrough(arrow_drawable, target_location, POINTS_PER_SQUARE);

                   //left_button_down = 1; //Set a flag to tell entire the system that the left mouse button is down.
               
               }

           } else if (event.mouseButton.button == sfMouseRight){
           
               //check if a widget is being clicked & process
               if (process_click_widgets( //This is an example of Guard Clause
                   mouse_screen_position.x,
                   mouse_screen_position.y,
                   1) == 1){ //The third argument is a flag to tell process_click_widgets that the widget is being right clicked
                   //do nothing
                   
               //or check if a monster is being clicked & process
               } else if (process_click_drawables(
                   mouse_viewport_position.x,
                   mouse_viewport_position.y,
                   1) == 1){
                   //The third argument is a flag to tell process_click_drawables that the drawable is being right clicked
               } else {
                   
                   //right click ground
                   right_button_down = 1;

               }

 
           } 
               
              
           
         
      
       } else if (event.type == sfEvtMouseButtonReleased) {
      
       //if right button up
           if (event.mouseButton.button == sfMouseRight) {
               right_button_down = 0;
           } else if (event.mouseButton.button == sfMouseLeft) {
               left_button_down = 0;
           }
       }

   }

}

int process_key_event(sfEvent event){

    switch(event.key.code){
            
        case sfKeyA:
            prompt_pass_char('a');
            break;
        case sfKeyB:
            prompt_pass_char('b');
            break;
        case sfKeyC:
            prompt_pass_char('c');
            break;
        case sfKeyD:
            prompt_pass_char('d');
            break;
        case sfKeyE:
            prompt_pass_char('e');
            break;
        case sfKeyF:
            prompt_pass_char('f');
            break;
        case sfKeyG:
            prompt_pass_char('g');
            break;
        case sfKeyH:
            prompt_pass_char('h');
            break;
        case sfKeyI:
            prompt_pass_char('i');
            break;
        case sfKeyJ:
            prompt_pass_char('j');
            break;
        case sfKeyK:
            prompt_pass_char('k');
            break;
        case sfKeyL:
            prompt_pass_char('l');
            break;
        case sfKeyM:
            prompt_pass_char('m');
            break;
        case sfKeyN:
            prompt_pass_char('n');
            break;
        case sfKeyO:
            prompt_pass_char('o');
            break;
        case sfKeyP:
            prompt_pass_char('p');
            break;
        case sfKeyQ:
            prompt_pass_char('q');
            break;
        case sfKeyR:
            prompt_pass_char('r');
            break;
        case sfKeyS:
            prompt_pass_char('s');
            break;
        case sfKeyT:
            prompt_pass_char('t');
            break;
        case sfKeyU:
            prompt_pass_char('u');
            break;
        case sfKeyV:
            prompt_pass_char('v');
            break;
        case sfKeyW:
            prompt_pass_char('w');
            break;
        case sfKeyX:
            prompt_pass_char('x');
            break;
        case sfKeyY:
            prompt_pass_char('y');
            break;
        case sfKeyZ:
            prompt_pass_char('z');
            break;
        case sfKeyReturn:
            prompt_pass_char('\n');
            break;
        case sfKeyEscape:
            exit(EXIT_SUCCESS);
            break;
        case sfKeyTab:
            //plot_potential(Fox_drawable_int);
            break;
        case sfKeyTilde:
            exit(11);
        case sfKeyDivide:
            prompt_pass_char('/'); //let prompt handle escape char
            break;
        default:
        break;
    }
    return 0;
}
