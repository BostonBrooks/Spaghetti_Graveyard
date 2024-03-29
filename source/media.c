#include "../headers/media.h"

//-----------------------------INCLUDES----------------------------//

#include "../headers/system_includes.h"
#include "../headers/constants.h"



//-----------------------------STRUCURES------------------------------//


//-----------------------------GLOBALS----------------------------//

sfTexture** sfTexture_vtable;
sfSprite** sfSprite_vtable;
bbAnimation** bbAnimation_vtable;

//-----------------------------FUNCTIONS--------------------------//

//for testing purposes
int print_next_line(FILE* Media) {
     //useful routine for debugging
    char test_string[512];
    fscanf(Media, "%511[^\n]", test_string);
    printf("%s\n", test_string);
    exit(1);
    return(193);
}

int sfTexture_vtable_alloc(int number) {
    sfTexture_vtable = (sfTexture**) malloc (sizeof(sfTexture*) * number);
    if (sfTexture_vtable == NULL)
        err(EXIT_FAILURE, "malloc");
}

int sfSprite_vtable_alloc(int number) {
    sfSprite_vtable = (sfSprite**) malloc (sizeof(sfSprite*) * number);
    if (sfSprite_vtable == NULL)
        err(EXIT_FAILURE, "malloc");
}

int bbAnimation_vtable_alloc(int number) {
    bbAnimation_vtable = (bbAnimation**) malloc (sizeof(bbAnimation*) * number);
    if (bbAnimation_vtable == NULL)
        err(EXIT_FAILURE, "malloc");
}

int sfTexture_to_vtable(int VAddress, char File[], sfBool smooth){

    sfTexture* New_Texture = sfTexture_createFromFile(File, NULL);
    assert(New_Texture != NULL);
    
    sfTexture_setSmooth(New_Texture, smooth);
    
    sfTexture_vtable[VAddress] = New_Texture;
}

int sfSprite_to_vtable(int VAddress, int TextureVAddress, int left, int top, int width,
    int height, float originx, float originy, float scalex, float scaley){

    sfSprite* New_Sprite = sfSprite_create();
    
    sfSprite_setTexture(New_Sprite, sfTexture_vtable[TextureVAddress], sfFalse);
    
    sfIntRect rectangle;
    
    rectangle.left = left;
    rectangle.top = top;
    rectangle.width = width;
    rectangle.height = height;
    
    sfSprite_setTextureRect(New_Sprite, rectangle);
    
    sfVector2f origin;
    
    origin.x = originx;
    origin.y = originy;
    
    sfSprite_setOrigin(New_Sprite, origin);
    
    sfVector2f scale;
    scale.x = scalex;
    scale.y = scaley;
    
    sfSprite_setScale(New_Sprite, scale);
    
    sfSprite_vtable[VAddress] = New_Sprite;
   
}

int bbAnimation_to_vtable(int VAddress, int Vdrawfunction, int angles, int frames, int framerate, int sprites[]){

    bbAnimation* animation = malloc (sizeof(bbAnimation) + sizeof(int) * angles * frames);

    if (animation == NULL)
        err(EXIT_FAILURE, "malloc");
    
    animation->Vdrawfunction = Vdrawfunction;
    animation->angles = angles;
    animation->frames = frames;
    animation->framerate = framerate;


    
    int i;
    
    for (i = 0; i < angles*frames; i++){
    
        animation->sprites[i] = sprites[i];

    
    }

    bbAnimation_vtable[VAddress] = animation; 


}

int Load_Media(){

// Input file


    FILE* Media = fopen("../maps/map0/media.csv", "r"); //STUB: this should not be hard-coded
    assert(Media != NULL);
    
    int return_value;
    int number;
    
// Textures
  //Ignore heading
  
    
    return_value = fscanf(Media, "\"sfTexture:\"%*[^\n]\n%*[^\n]\n");
    assert (return_value == 0);
    
  //number of textures to allocate
    return_value = fscanf(Media, "\"Number of Textures:\",%d%*[^\n]\n%*[^\n]\n", &number);
    

    assert (return_value == 1);
    

    
    sfTexture_vtable_alloc(number);
    
  //Ignore table heading
    return_value = fscanf(Media, "\"VAddress\",\"File\",\"Smooth:\"%*[^\n]\n%*[^\n]\n");
    assert (return_value == 0);
    
    int VAddress;
    char File_Name[100];
    char Smooth;
    
  //Load textures one by one
    while((return_value = fscanf(Media, "%d,\"%99[^\"]\",\"%c\"%*[^\n]\n", &VAddress, &File_Name[0], &Smooth)) == 3){
        
        
        if (Smooth == 'T') {
            sfTexture_to_vtable(VAddress, File_Name, sfTrue);
        } else  {
            sfTexture_to_vtable(VAddress, File_Name, sfFalse);
        }
    }

// Sprites

  //Ignore Heading
    return_value = fscanf(Media, "%*[^\n]\n\"sfSprite:\"%*[^\n]\n%*[^\n]\n");
    assert (return_value == 0);
    
    
    
  //number of sprites to allocate
    return_value = fscanf(Media, "\"Number of Sprites:\",%d%*[^\n]\n%*[^\n]\n", &number);

    assert (return_value == 1);
    

    
    sfSprite_vtable_alloc(number);
    
  //Ignore table heading
    return_value = fscanf(Media, "\"label\",\"VAddress\",\"sfTexture\",\"left\",\"top\",\"width\",\"height\",\"originx\",\"originy\",\"scalex\",\"scaley\"%*[^\n]\n%*[^\n]\n");
    assert (return_value == 0);
    
  //create sprites one by one
    char Label[100];
    //int VAddress;
    int TextureVAddress;
    int left, top, width, height;
    float originx, originy;
    float scalex, scaley;
    

  //Load sprites one by one
    while((return_value = fscanf(Media, "\"%99[^\"]\",%d,%d,%d,%d,%d,%d,%f,%f,%f,%f%*[^\n]\n",
     &Label[0], &VAddress, &TextureVAddress, &left, &top, &width, &height,
      &originx, &originy, &scalex, &scaley)) == 11){
        
        sfSprite_to_vtable(VAddress, TextureVAddress, left, top, width, height,
         originx, originy, scalex, scaley);
        
         
    }
// Animations    

    //char Label[100]
    //int VAddress;
    int Vdrawfunction;
    int angles;
    int frames;
    int framerate;
    int sprites[256];  //maximum amount of sprites per animation is currently only 256
    
  //Ignore Heading
  
    return_value = fscanf(Media, "%*[^\n]\n\"Animation:\"%*[^\n]\n%*[^\n]\n");
    assert (return_value == 0);
    
    return_value = fscanf(Media, "\"Number of Animations:\",%d%*[^\n]\n%*[^\n]\n", &number);
    
    
    assert (return_value == 1);
    
    bbAnimation_vtable_alloc(number);
    
  //Ignore table heading
  
    return_value = fscanf(Media, "\"label\",\"VAddress\",\"Vdrawfunction\",\"angles\",\"frames\",\"framerate\",\"sprites[]\"%*[^\n]\n%*[^\n]\n");
    assert (return_value == 0);
    
  //Load animations one by one
    int i;
    while((return_value = fscanf(Media, "\"%99[^\"]\",%d,%d,%d,%d,%d",
     &Label[0], &VAddress, &Vdrawfunction, &angles, &frames, &framerate)) == 6){

        //printf("\n%s\n", Label);    //debug
        
        for (i = 0; i < angles * frames; i++){
            fscanf(Media, ",%d", &sprites[i]);
            //printf("sprite = %d\n", sprites[i]); //debug
        }
        fscanf(Media, "%*[^\n]\n");
        bbAnimation_to_vtable(VAddress, Vdrawfunction, angles, frames, framerate, sprites);

    }
    
    //return_value = fscanf(Media, "%*[^\n]\n%*[^\n]\n\"End:\"%*[^\n]");
    //if (return_value == 0){
    //    printf("vaddress = %d\n", VAddress);
    //    assert(0==1);
    //};
    
    
    fclose(Media);
    
}


sfSprite* bbAnimation_getSprite(int animation_int, int angle_int, int frame_int){
//TODO test for non-negative inputs
    bbAnimation* animation = bbAnimation_vtable[animation_int];
    int sprite_int = (animation->frames)*angle_int + frame_int/animation->framerate;
    int sprite_num = animation->sprites[sprite_int];


//TODO why do we get a -1 here?

    if (sprite_num == -1) return sfSprite_vtable[44];
    return sfSprite_vtable[sprite_num];
    
}

int bbAnimation_print_data(int animation_int){

        bbAnimation* animation = bbAnimation_vtable[animation_int];
        int Vdrawfunction = animation->Vdrawfunction;
        int angles = animation->angles;
        int frames = animation->frames;
        int framerate = animation->framerate;
        int* sprites = animation->sprites;

        printf("drawfunction = %d, angles = %d, frames = %d, framerate = %d", Vdrawfunction, angles, frames, framerate);

        for(int i = 0; i < angles*frames; i++){
            printf(", %d", sprites[i]);
        }

        printf("\n");


}