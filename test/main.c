#define MAIN

#define BBWIDGET_H   //Prevent this from being included

#ifndef ALL_INCLUDES
#define ALL_INCLUDES
#include "../headers/all_includes.h"
#endif


int Current_Time = 0;
int player_int;
int player_hp = 100;

int damage_player(int x){
    bbAIControl* player_AI = bbAIControl_Pool_Lookup(player_int);
    bbDrawable* drawable = bbDrawable_Pool_Lookup(player_AI->drawables[0]);

    drawable->health = drawable->health - 5;
    player_hp = drawable->health;
    if(drawable->health <= 0) {
        printf("Now you're dead!\n");
        exit(1);
    }
}
int heal_player(int x){
    bbAIControl* player_AI = bbAIControl_Pool_Lookup(player_int);
    bbDrawable* drawable = bbDrawable_Pool_Lookup(player_AI->drawables[0]);

    drawable->health = drawable->health + 50;
    player_hp = drawable->health;
    if(drawable->health <= 0) {
        printf("Now you're dead!\n");
        exit(1);
    }
}

sfRectangleShape* Health_Bar;

int init_health(){
    Health_Bar = sfRectangleShape_create();
    sfColor dark_red = sfColor_fromRGB(188, 0, 0);
    sfRectangleShape_setFillColor(Health_Bar, dark_red);
    sfVector2f position;
    position.x = 62;
    position.y = 530;
    sfRectangleShape_setPosition(Health_Bar, position);
    position.x = -13;
    position.y = -449;
    sfRectangleShape_setSize(Health_Bar, position);
}

int display_health(){
    sfVector2f size;
    size.x = -13;
    size.y = -449 * player_hp / 100;

    sfRectangleShape_setSize(Health_Bar, size);

    sfRenderWindow_drawRectangleShape(window, Health_Bar, NULL);
}

int viewpoint_drawable_int; 

int Test_All(void);

int main (void){

    printf("Program Starting:\n");

    bbDebug("This is a debug message %f\n", 193.1);

    bbVerbose("This is a verbose message %d\n", 193);

    Test_All();
    
    sleep(1);
    
    exit(0);


}

int Test_All(void){



    Window_Init();

    sfColor beige = COLOUR_BEIGE;
    sfColor dark_brown = COLOUR_DARKBROWN;
    sfVector2f position = {50, 440};
    
    sfFont* font = sfFont_createFromFile("../graphics/Bowman.ttf");
    if (!font) return EXIT_FAILURE;
    sfText* text = sfText_create();
    sfText_setString(text, "Hello Spaghetti Graveyard!");
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 128);
    sfText_setColor(text, dark_brown);
    sfText_setPosition(text, position);
    
    sfRenderWindow_drawText(window, text, NULL);
    sfRenderWindow_display(window);
    
    //Setting the angle of the sun.
    LightIncedence.i = 1;
    LightIncedence.j = 1;
    LightIncedence.k = 1;
    
    //Setting the position of the viewer.
    viewpoint.i = 2000;
    viewpoint.j = 3000;
    viewpoint.k = 0;

    //setting the direction the viewer is travelling
    bbMapCoords goalpoint;
    goalpoint.i = 2000;
    goalpoint.j = 3000;
    goalpoint.k = 0;


        
    bbDrawable_Pool_Make_Null();

    
    bbAIControl_Pool_Make_Null();


    
    Load_Media();

	//bbWidget_Pool_Make_Null();
	//bbWidget_Init_Tables();
	//root_widget = bbWidget_Init_Widgets();

    bbSkin_init();

    
    bbTerrainSquare_initAll();

    
    bbElevations_load();

    
    
    bbViewport_init();

    
    
    bbGroundSurface_initAll();

    
    bbDrawfunction_initAll();

    
    bbAIControl_init();

        
    bbMessage_initTypes();

    
    potential_avoidance_initShapes();
    Sum_Forces_initShapes();

    
    Create_Ground_Shaders();
    

    prompt_init();
    

    char string2[1000];
    sfText* text2 = sfText_create();
    sfText_setString(text2, "Hello SFML");
    sfText_setFont(text2, font);
    sfText_setCharacterSize(text2, 50);
    sfVector2f text_position;
    text_position.x = 0;
    text_position.y = 150;
    sfText_setPosition(text2, text_position);

    player_int = bbAI_constructor_vtable[PLAYER_20230829](viewpoint);
    bbAIControl* player_AI = bbAIControl_Pool_Lookup(player_int);
    viewpoint_drawable_int = player_AI->drawables[0];

    init_health();

    
    
    bbMapCoords mc;   
    
    for (int i=0; i<8; i++){
    
        float i = rand() % (POINTS_PER_SQUARE * 5);
        float j = rand() % (POINTS_PER_SQUARE * 5);
    
        mc.i = i;
        mc.j = j;
        mc.k = 0;
        
        bbMapCoords_updateElevation(&mc);
    
        bbAI_constructor_vtable[AI_SNAIL](mc);
        
        //#ifdef DEBUG
        //printf("AI pool head = %d, AI pool tail = %d\n", bbAIControl_Pool_In_Use_Head, bbAIControl_Pool_In_Use_Tail);
        //#endif
           
        //#ifdef DEBUG
        //printf("AI available head = %d, AI available tail = %d\n", bbAIControl_Pool_Available_Head, bbAIControl_Pool_Available_Tail);
        //#endif   
    }
    for (int i=0; i<8; i++){

        float i = rand() % (POINTS_PER_SQUARE * 5);
        float j = rand() % (POINTS_PER_SQUARE * 5);

        mc.i = i;
        mc.j = j;
        mc.k = 0;

        bbMapCoords_updateElevation(&mc);

        bbDrawable_new_tree(mc);

        //#ifdef DEBUG
        //printf("AI pool head = %d, AI pool tail = %d\n", bbAIControl_Pool_In_Use_Head, bbAIControl_Pool_In_Use_Tail);
        //#endif

        //#ifdef DEBUG
        //printf("AI available head = %d, AI available tail = %d\n", bbAIControl_Pool_Available_Head, bbAIControl_Pool_Available_Tail);
        //#endif
    }




    sfRenderTexture_drawSprite(viewport, sfSprite_vtable[28], NULL); //viewport background
    

    
    while(1) {



       // bbVerbose("Beginning Main Loop: time = %d\n", Current_Time);

        sfEvent event;

        input_process();
        

        
        bbAIControl_updatePool();
                

        
        bbMessage_processAll();
        

        
        bbDrawable* viewpoint_drawable
             = bbDrawable_Pool_Lookup(viewpoint_drawable_int);
        viewpoint = viewpoint_drawable->location;
        viewpoint.k = viewpoint.k *0.5 + 200;

    
        bbTerrainSquare_drawVisible();
        bbGroundSurface_drawVisible(); 
        sfRenderTexture_display(viewport); 
        sfRenderWindow_drawSprite(window, viewport_sprite, &bbViewport_renderer);
        Display_Decal();

		//bbWidget_Draw(root_widget);
        prompt_display();
        display_health();
        sfRenderWindow_display(window);

        sfRenderTexture_clear(bbViewport_background, sfBlue);
        sfRenderTexture_clear(bbViewport_ground, sfTransparent);
        sfRenderTexture_clear(bbViewport_main, sfTransparent);
        sfRenderTexture_clear(bbViewport_highlights, sfTransparent);
        sfRenderTexture_clear(bbViewport_healthbars, sfTransparent);
        
        Current_Time++;



    }





}

void err( int eval,
          const char *fmt, ...){
    printf("%s\n", fmt);
    exit(eval);
}
