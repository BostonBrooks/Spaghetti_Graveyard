#define MAIN

#ifndef ALL_INCLUDES
#define ALL_INCLUDES
#include "../headers/all_includes.h"
#endif


int Current_Time = 0;

int viewpoint_drawable_int; 

int Test_All(void);

int main (void){

    printf("Program Starting:\n");
    
    Test_All();
    
    sleep(1);
    
    exit(0);


}

int Test_All(void){

    Window_Init();

    sfColor beige = COLOUR_BEIGE;
    sfColor dark_brown = COLOUR_DARKBROWN;
    sfVector2f position = {50, 440};
    
    sfFont* font = sfFont_createFromFile("../media/Bowman.ttf");
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
    
    
    
    #ifdef VERBOSE
        printf("bbDrawable_Pool_Make_Null();\n");
    #endif
        
    bbDrawable_Pool_Make_Null();
    
    #ifdef VERBOSE
        printf("bbAIControl_Pool_Make_Null();\n");
    #endif
    
    bbAIControl_Pool_Make_Null();
    

    
    
    #ifdef VERBOSE
        printf("Load_Media();\n");
    #endif
    
    Load_Media();

    //#ifdef DEBUG
    //bbAnimation_print_data(18);
    //bbAnimation_print_data(19);
    //#endif

    #ifdef VERBOSE
        printf("bbTerrainSquare_initAll();\n");
    #endif
    
    bbTerrainSquare_initAll();
    
    #ifdef VERBOSE
        printf("bbElevations_load();\n");
    #endif
    
    bbElevations_load();
    
    #ifdef VERBOSE
        printf("bbViewport_init();\n");
    #endif
    
    
    bbViewport_init();
    
    #ifdef VERBOSE
        printf("bbGroundSurface_initAll();\n");
    #endif
    
    
    bbGroundSurface_initAll();
    
    #ifdef VERBOSE
        printf("bbDrawfunction_initAll();\n");
    #endif
    
    
    bbDrawfunction_initAll();
    
    #ifdef VERBOSE
        printf("bbAIControl_initTypes();\n");
    #endif
    
    
    bbAIControl_init();
    

    
    
    #ifdef VERBOSE
        printf("bbMessage_initTypes();\n");
    #endif
        
    bbMessage_initTypes();
    
    #ifdef VERBOSE
        printf("potential_avoidance_initShapes();\n");
    #endif
    
    potential_avoidance_initShapes();
    Sum_Forces_initShapes();
    
    #ifdef VERBOSE
        printf("Create_Ground_Shaders();\n");
    #endif
    
    Create_Ground_Shaders();
    
    #ifdef VERBOSE
        printf("prompt_init();\n");
    #endif
    
    prompt_init();
    
    #ifdef VERBOSE
        printf("some text stuff\n");
    #endif
    
    char string2[1000];
    sfText* text2 = sfText_create();
    sfText_setString(text2, "Hello SFML");
    sfText_setFont(text2, font);
    sfText_setCharacterSize(text2, 50);
    sfVector2f text_position;
    text_position.x = 0;
    text_position.y = 150;
    sfText_setPosition(text2, text_position);
    
    #ifdef VERBOSE
        printf("Spawn some null AIs\n");
    #endif
    
    

    
    
    bbMapCoords mc;   
    
    for (int i=0; i<64; i++){
    
        float i = rand() % (POINTS_PER_SQUARE * 5);
        float j = rand() % (POINTS_PER_SQUARE * 5);
    
        mc.i = i;
        mc.j = j;
        mc.k = 0;
        
        bbMapCoords_updateElevation(&mc);
    
        bbAI_constructor_vtable[AI_TORTOISE](mc);
        
        //#ifdef DEBUG
        //printf("AI pool head = %d, AI pool tail = %d\n", bbAIControl_Pool_In_Use_Head, bbAIControl_Pool_In_Use_Tail);
        //#endif
           
        //#ifdef DEBUG
        //printf("AI available head = %d, AI available tail = %d\n", bbAIControl_Pool_Available_Head, bbAIControl_Pool_Available_Tail);
        //#endif   
    }
    
    #ifdef VERBOSE
        printf("Spawn player AI\n");
    #endif    

    int player_int = bbAI_constructor_vtable[PLAYER_20230829](viewpoint);
    bbAIControl* player_AI = bbAIControl_Pool_Lookup(player_int);
    viewpoint_drawable_int = player_AI->drawables[0];
    
    


    sfRenderTexture_drawSprite(viewport, sfSprite_vtable[28], NULL); //viewport background
    

    
    while(1) {
    
        
        #ifdef VERBOSE
        printf("Beginning Main Loop: time = %d\n", Current_Time);
        #endif   
        sfEvent event;
        
        
        #ifdef VERBOSE
        printf("User Input:\n");
        #endif 
        input_process();
        
        
        #ifdef VERBOSE
        printf("bbAIControl_updatePool();\n");
        #endif 
        
        bbAIControl_updatePool();
                
        #ifdef VERBOSE
        printf("bbMessage_processAll();\n");
        #endif 
        
        bbMessage_processAll();
        
        #ifdef VERBOSE
        printf("Centre view on viewpoint_drawable_int\n");
        #endif 
        
        bbDrawable* viewpoint_drawable
             = bbDrawable_Pool_Lookup(viewpoint_drawable_int);
        viewpoint = viewpoint_drawable->location;
        viewpoint.k *= 0.5;
        
        #ifdef VERBOSE
        printf("Draw to Screen:\n");
        #endif
    
        bbTerrainSquare_drawVisible();
        bbGroundSurface_drawVisible(); 
        sfRenderTexture_display(viewport); 
        sfRenderWindow_drawSprite(window, viewport_sprite, &bbViewport_renderer);
        Display_Decal();
        prompt_display();
        sfRenderWindow_display(window);
        
        #ifdef VERBOSE
        printf("Clear Screen:\n");
        #endif 
        sfRenderTexture_clear(bbViewport_background, sfBlue);
        sfRenderTexture_clear(bbViewport_ground, sfTransparent);
        sfRenderTexture_clear(bbViewport_main, sfTransparent);
        sfRenderTexture_clear(bbViewport_highlights, sfTransparent);
        sfRenderTexture_clear(bbViewport_healthbars, sfTransparent);
        
        Current_Time++;
    }
    
    
    
    
    
    
}
