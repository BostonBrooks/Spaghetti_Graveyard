#define BBDRAWABLE_PLOT
//-----------------------------INCLUDES----------------------------//

#ifndef CONSTANTS
#define CONSTANTS
#include "../headers/constants.h"
#endif

#ifndef SYSTEM_INCLUDES
#define SYSTEM_INCLUDES
#include "../headers/system_includes.h"
#endif

#ifndef VIEWPORT
#define VIEWPORT
#include "../headers/viewport.h"
#endif

#ifndef GEOMETRY
#define GEOMETRY
#include "../headers/geometry.h"
#endif

#ifndef BBDRAWABLE
#define BBDRAWABLE
#include "../headers/bbDrawable.h"
#endif

#ifndef BBDRAWABLE_LISTS
#define BBDRAWABLE_LISTS
#include "../headers/bbDrawable_lists.h"
#endif

#ifndef BBGROUNDSURFACE
#define BBGROUNDSURFACE
#include "../headers/bbGroundSurface.h"
#endif

#ifndef BBSKIN
#define BBSKIN
#include "../headers/bbSkin.h"
#endif

#ifndef MEDIA
#define MEDIA
#include "../headers/media.h"
#endif

//-----------------------------GLOBALS----------------------------//



int (*bbDrawfunction_vtable[NUMBER_OF_DRAW_FUNCTIONS])(bbDrawable* tobedrawn, int i);
extern int Current_Time; //TODO this should be in a header/code file

sfCircleShape* Circle;

//-----------------------------CODE----------------------------//
int bbDrawable_plot(bbDrawable* tobedrawn){



   int i;
   
   for (i=0; i < ANIMATIONS_PER_DRAWABLE; i++){
   
       if (tobedrawn->drawfunction[i] >= 0){
           bbDrawfunction_vtable[tobedrawn->drawfunction[i]](tobedrawn, i);
       }
   }
   
   //if (tobedrawn->display_health_until != NO_HEALTHBAR
   // && tobedrawn->display_health_until <= Current_Time)
   
   if (tobedrawn->display_health_until != NO_HEALTHBAR && tobedrawn->display_health_until >= Current_Time){
    
        bbMapCoords mc = tobedrawn->location;
        bbScreenCoords sc = bbMapCoords_getScreenCoords_centre(mc);
        
        float top, bottom, left, middle, right;
        
        float health_bar_height = tobedrawn->health_bar_height;
        float health_bar_width = tobedrawn->health_bar_width;
        float health_bar_length = tobedrawn->health_bar_length;
        float health = tobedrawn->health;
        float max_health = tobedrawn->max_health;
        
        
        bottom = sc.y - health_bar_height;
        top = bottom - health_bar_width;
        left = sc.x - health_bar_length/2.0;
        middle = left + health_bar_length * (health*1.0) / max_health;
        right = left + health_bar_length;
        
        sfVertex points[4];

        points[0].color = sfRed;
        points[1].color = sfRed;
        points[2].color = sfRed;
        points[3].color = sfRed;
        
        
        points[0].position.x = left;
        points[0].position.y = top;
        points[1].position.x = right;
        points[1].position.y = top;
        points[2].position.x = left;
        points[2].position.y = bottom;
        points[3].position.x = right;
        points[3].position.y = bottom;
        
        sfRenderTexture_drawPrimitives 	( 	bbViewport_healthbars,
		                                &points[0],
		                                4,
		                                sfTrianglesStrip,
		                                NULL//const sfRenderStates *  	states 
	                                );
	                                
	                                

        points[0].color = sfGreen;
        points[1].color = sfGreen;
        points[2].color = sfGreen;
        points[3].color = sfGreen;
        
        
        points[0].position.x = left;
        points[0].position.y = top;
        points[1].position.x = middle;
        points[1].position.y = top;
        points[2].position.x = left;
        points[2].position.y = bottom;
        points[3].position.x = middle;
        points[3].position.y = bottom;
        
        sfRenderTexture_drawPrimitives 	( 	bbViewport_healthbars,
		                                &points[0],
		                                4,
		                                sfTrianglesStrip,
		                                NULL//const sfRenderStates *  	states 
	                                );
        
    }
   
    if(tobedrawn->cosmetic_radius > 0) //or whatever else conditions?
    {
        sfCircleShape_setRadius(Circle, tobedrawn->cosmetic_radius);
        
        sfVector2f origin;
        origin.x = tobedrawn->cosmetic_radius;
        origin.y = tobedrawn->cosmetic_radius;
        sfCircleShape_setOrigin(Circle, origin);
      
        bbMapCoords mc = tobedrawn->location;
        bbSquareCoords sc = bbMapCoords_getSquareCoords (mc);
        if (sc.i < 0 || sc.j < 0 || sc.i >= SQUARES_PER_MAP || sc.j >= SQUARES_PER_MAP) return 0;
    
        bbGroundSurface* Ground_Surface = &bbGroundSurface_grid[sc.i][sc.j];
    
        int pointi = mc.i - sc.i*POINTS_PER_PIXEL * PIXELS_PER_TILE * TILES_PER_SQUARE;
        int pointj = mc.j - sc.j*POINTS_PER_PIXEL * PIXELS_PER_TILE * TILES_PER_SQUARE;
    
        int pixeli = floordiv(pointi, POINTS_PER_PIXEL);
        int pixelj = floordiv(pointj, POINTS_PER_PIXEL);
    
        sfVector2f position;
        position.x = pixelj;
        position.y = pixeli;
    
        sfCircleShape_setPosition(Circle, position);
    
    
        sfRenderTexture* Circles = Ground_Surface->Circles_Render_Texture;
        sfRenderTexture_drawCircleShape(Circles, Circle, NULL);
      
      
      
    
    }
    return 0;
}

int bbDrawable_plot_int(int tobedrawn_int){

   bbDrawable* tobedrawn = bbDrawable_Pool_Lookup(tobedrawn_int);

   int i;
   
   for (i=0; i < ANIMATIONS_PER_DRAWABLE; i++){
   
       if (tobedrawn->drawfunction[i] >= 0){
           bbDrawfunction_vtable[tobedrawn->drawfunction[i]](tobedrawn, i);
       }
   }

   if (tobedrawn->display_health_until != NO_HEALTHBAR
    && tobedrawn->display_health_until <=Current_Time){
    
        bbMapCoords mc = tobedrawn->location;
        bbScreenCoords sc = bbMapCoords_getScreenCoords_centre(mc);
        
        float top, bottom, left, middle, right;
        
        float health_bar_height = tobedrawn->health_bar_height;
        float health_bar_width = tobedrawn->health_bar_width;
        float health_bar_length = tobedrawn->health_bar_length;
        float health = tobedrawn->health;
        float max_health = tobedrawn->max_health;
        
        
        bottom = sc.x - health_bar_height;
        top = bottom - health_bar_width;
        left = sc.x - health_bar_length/2.0;
        middle = left + health_bar_length * (health*1.0) / max_health;
        right = left + health_bar_length;
        
        sfVertex points[4];

        points[0].color = sfRed;
        points[1].color = sfRed;
        points[2].color = sfRed;
        points[3].color = sfRed;
        
        
        points[0].position.x = left;
        points[0].position.y = top;
        points[1].position.x = right;
        points[1].position.y = top;
        points[2].position.x = left;
        points[2].position.y = bottom;
        points[3].position.x = right;
        points[3].position.y = bottom;
        
        sfRenderTexture_drawPrimitives 	( 	bbViewport_healthbars,
		                                &points[0],
		                                4,
		                                sfTrianglesStrip,
		                                NULL//const sfRenderStates *  	states 
	                                );
	                                
	                                

        points[0].color = sfGreen;
        points[1].color = sfGreen;
        points[2].color = sfGreen;
        points[3].color = sfGreen;
        
        
        points[0].position.x = left;
        points[0].position.y = top;
        points[1].position.x = middle;
        points[1].position.y = top;
        points[2].position.x = middle;
        points[2].position.y = bottom;
        points[3].position.x = right;
        points[3].position.y = bottom;
        
        sfRenderTexture_drawPrimitives 	( 	bbViewport_healthbars,
		                                &points[0],
		                                4,
		                                sfTrianglesStrip,
		                                NULL//const sfRenderStates *  	states 
	                                );
        
    }
    
    
    
   return 0;

}

int bbDrawable_plotPool(void){

    int tobedrawn_int = bbDrawable_Pool_In_Use_Head;
    
    if ( tobedrawn_int == -1) return 0;
    
    while (tobedrawn_int != -1){
        bbDrawable* tobedrawn = bbDrawable_Pool_Lookup(tobedrawn_int);
        bbDrawable_plot(tobedrawn);
        tobedrawn_int = tobedrawn->Pool_Next;
        
    }
    return 0;
}

int basicdraw(bbDrawable* tobedrawn, int i){
    int animation = tobedrawn->animation[i];
    int angle = tobedrawn->angle[i];
    int frame = tobedrawn->frame[i];
    
    bbMapCoords mc = tobedrawn->location;
    bbScreenCoords sc = bbMapCoords_getScreenCoords_centre(mc);
    
    //printf("x=%f, y=%f\n", sc.x, sc.y); 
    
    sfVector2f position;
    position.x = sc.x;
    position.y = sc.y;
    
    sfSprite* sprite = bbAnimation_getSprite(animation,angle,frame);
    
    sfSprite_setPosition(sprite, position);
    sfRenderTexture_drawSprite(bbViewport_main, sprite, NULL);
    
    
    
    return 0;
}

int nulldraw(bbDrawable* tobedrawn, int i){
    int animation = tobedrawn->animation[i];
    int angle = tobedrawn->angle[i];
    int frame = tobedrawn->frame[i];
    
    bbMapCoords mc = tobedrawn->location;
    bbScreenCoords sc = bbMapCoords_getScreenCoords_centre(mc);
    
    sfVector2f position;
    position.x = sc.x;
    position.y = sc.y;
    
    sfSprite* sprite = sfSprite_vtable[0];
    
    sfSprite_setPosition(sprite, position);
    sfRenderTexture_drawSprite(bbViewport_main, sprite, NULL);
    
    return 0;
}

int repeatdraw(bbDrawable* tobedrawn, int i){

//#ifdef DEBUG
//    printf("before accessing drawable struct\n");
//#endif
    int animation = tobedrawn->animation[i];


//#ifdef DEBUG
//    printf("animation = %d\n", animation);
//#endif

    int angle = tobedrawn->angle[i];
    int frame = tobedrawn->frame[i];

//#ifdef DEBUG
//    printf("after accessing drawable struct\n");
//#endif
    
    bbMapCoords mc = tobedrawn->location;


//#ifdef DEBUG
//    printf("mc.i = %d, mc.j = %d, mc.k = %d\n", mc.i, mc.j, mc.k);
//#endif

    bbScreenCoords sc = bbMapCoords_getScreenCoords_centre(mc);
    
    sfVector2f position;
    position.x = sc.x;
    position.y = sc.y;


//#ifdef DEBUG
//    printf("position.x = %f, position.y = %f\n", position.x, position.y);
//#endif

//#ifdef DEBUG
//    printf("animation = %d, angle = %d, frame = %d\n", animation, angle, frame);
//#endif

    sfSprite* sprite = bbAnimation_getSprite(animation, angle, frame);

//#ifdef DEBUG
//    printf("after accessing sfSprite\n");
//#endif



    sfSprite_setPosition(sprite, position);

//#ifdef DEBUG
//    printf("after modifying sfSprite\n");
//#endif
    sfRenderTexture_drawSprite(bbViewport_main, sprite, NULL);
    
    bbAnimation* anim = bbAnimation_vtable[animation];
    
    int frames = anim->frames;
    int framerate = anim->framerate;
    
    tobedrawn->frame[i] = (frame+1)%(frames*framerate);
    
    return 0;
}

int angles_8 (float i, float j);

int repeatdraw_skin(bbDrawable* tobedrawn, int i){

//#ifdef DEBUG
//    printf("repeatdraw_skin\n");
//#endif
//#ifdef DEBUG
//    printf("0 tobedrawn = %d\n", tobedrawn->Pool_Self);
//#endif

    int skin_int = -7;
    int state_int = -11;

    int animation = tobedrawn->animation[i];
    if (animation == ANIMATION_NONE) return 0;
    if (animation == ANIMATION_SKIN) {

        //lookup animation from skin

        skin_int = tobedrawn->skin;
        state_int = tobedrawn->state;

        assert(state_int >= 0 && state_int < INNER_STATES_PER_SKIN);

        animation = bbSkins[skin_int].animations_int[state_int][i];
        //printf("animation = %d\n", animation);

    }

//#ifdef DEBUG
//    printf("animation = %d\n", animation);
//#endif

    int angle = tobedrawn->angle[i];
    int frame = tobedrawn->frame[i];

//#ifdef DEBUG
//    printf("after accessing drawable struct\n");
//#endif


//#ifdef DEBUG
//    printf("1 tobedrawn = %d\n", tobedrawn->Pool_Self);
//#endif

    bbMapCoords mc = tobedrawn->location;


//#ifdef DEBUG
//    printf("mc.i = %d, mc.j = %d, mc.k = %d\n", mc.i, mc.j, mc.k);
//#endif

    bbScreenCoords sc = bbMapCoords_getScreenCoords_centre(mc);

    sfVector2f position;
    position.x = sc.x;
    position.y = sc.y;


//#ifdef DEBUG
//    printf("position.x = %f, position.y = %f\n", position.x, position.y);
//#endif

//#ifdef DEBUG
//    printf("i = %d, skin = %d, state = %d, animation = %d, angle = %d, frame = %d\n",i, skin_int,state_int,  animation, angle, frame);
//#endif

//#ifdef DEBUG
//    printf("2 tobedrawn = %d\n", tobedrawn->Pool_Self);
//#endif

    sfSprite* sprite = bbAnimation_getSprite(animation, angle, frame);



//#ifdef DEBUG
//    printf("after accessing sfSprite\n");
//#endif

//#ifdef DEBUG
//    printf("3 tobedrawn = %d\n", tobedrawn->Pool_Self);
//#endif

    sfSprite_setPosition(sprite, position);

//#ifdef DEBUG
//    printf("4 tobedrawn = %d\n", tobedrawn->Pool_Self);
//#endif
//#ifdef DEBUG
//    printf("after modifying sfSprite\n");
//#endif
    sfRenderTexture_drawSprite(bbViewport_main, sprite, NULL);




    bbAnimation* anim = bbAnimation_vtable[animation];

    int frames = anim->frames;
    int framerate = anim->framerate;

    tobedrawn->frame[i] = (frame+1)%(frames*framerate);
    //printf("frame = %d\n", tobedrawn->frame[i]);



    return 0;
}

int draw_once_skin(bbDrawable* tobedrawn, int i){

    //printf("Draw once skin\n");
//#ifdef DEBUG
//    printf("before accessing drawable struct\n");
//#endif
//#ifdef DEBUG
//    printf("0 tobedrawn = %d\n", tobedrawn->Pool_Self);
//#endif
    int skin_int = -7;
    int state_int = -11;

    int animation = tobedrawn->animation[i];
    if (animation == ANIMATION_NONE) return 0;
    if (animation == ANIMATION_SKIN) {

        //lookup animation from skin

        skin_int = tobedrawn->skin;
        state_int = tobedrawn->state;

        assert(state_int >= 0 && state_int < INNER_STATES_PER_SKIN);

        animation = bbSkins[skin_int].animations_int[state_int][i];
        //printf("animation = %d\n", animation);

    }

//#ifdef DEBUG
//    printf("animation = %d\n", animation);
//#endif

    int angle = tobedrawn->angle[i];
    int frame = tobedrawn->frame[i];

//#ifdef DEBUG
//    printf("after accessing drawable struct\n");
//#endif


//#ifdef DEBUG
//    printf("1 tobedrawn = %d\n", tobedrawn->Pool_Self);
//#endif

    bbMapCoords mc = tobedrawn->location;


//#ifdef DEBUG
//    printf("mc.i = %d, mc.j = %d, mc.k = %d\n", mc.i, mc.j, mc.k);
//#endif

    bbScreenCoords sc = bbMapCoords_getScreenCoords_centre(mc);

    sfVector2f position;
    position.x = sc.x;
    position.y = sc.y;


//#ifdef DEBUG
//    printf("position.x = %f, position.y = %f\n", position.x, position.y);
//#endif

//#ifdef DEBUG
//    printf("i = %d, skin = %d, state = %d, animation = %d, angle = %d, frame = %d\n",i, skin_int,state_int,  animation, angle, frame);
//#endif

//#ifdef DEBUG
//    printf("2 tobedrawn = %d\n", tobedrawn->Pool_Self);
//#endif

    sfSprite* sprite = bbAnimation_getSprite(animation, angle, frame);



//#ifdef DEBUG
//    printf("after accessing sfSprite\n");
//#endif

//#ifdef DEBUG
//    printf("3 tobedrawn = %d\n", tobedrawn->Pool_Self);
//#endif

    sfSprite_setPosition(sprite, position);

//#ifdef DEBUG
//    printf("4 tobedrawn = %d\n", tobedrawn->Pool_Self);
//#endif
//#ifdef DEBUG
//    printf("after modifying sfSprite\n");
//#endif
    sfRenderTexture_drawSprite(bbViewport_main, sprite, NULL);




    bbAnimation* anim = bbAnimation_vtable[animation];

    int frames = anim->frames;
    int framerate = anim->framerate;

    if (tobedrawn->frame[i] < frames*framerate - 1) {
        tobedrawn->frame[i] = tobedrawn->frame[i] + 1;
    }




    return 0;
}

int balloondraw(bbDrawable* tobedrawn, int i){

    bbMapCoords mc = tobedrawn->location;
    
    

    int animation = tobedrawn->animation[i];
    int angle = tobedrawn->angle[i];
    int frame = tobedrawn->frame[i];
    
    bbAnimation* anim = bbAnimation_vtable[animation];
    
    int frames = anim->frames;
    int framerate = anim->framerate;
    
    
    mc = tobedrawn->location;
    mc.k += 160 + 160 * sin(2.0*M_PI*frame/(frames*framerate));
    bbScreenCoords sc = bbMapCoords_getScreenCoords_centre(mc);
    
    sfVector2f position;
    position.x = sc.x;
    position.y = sc.y;
    
    sfSprite* sprite = bbAnimation_getSprite(animation,angle,frame);
    
    sfSprite_setPosition(sprite, position);
    sfRenderTexture_drawSprite(bbViewport_main, sprite, NULL);
    
    
    tobedrawn->frame[i] = (frame+1)%(frames*framerate);
    
    return 0;
}

int shadowdraw(bbDrawable* tobedrawn, int i){
    int animation = tobedrawn->animation[i];
    int angle = tobedrawn->angle[i];
    int frame = tobedrawn->frame[i];
    sfSprite* sprite = bbAnimation_getSprite(animation,angle,frame);
    
    bbMapCoords mc = tobedrawn->location;
    bbSquareCoords sc = bbMapCoords_getSquareCoords (mc);
    if (sc.i < 0 || sc.j < 0 || sc.i >= SQUARES_PER_MAP || sc.j >= SQUARES_PER_MAP) return 0;
    bbGroundSurface* Ground_Surface = &bbGroundSurface_grid[sc.i][sc.j];
    
    int pointi = mc.i - sc.i*POINTS_PER_PIXEL * PIXELS_PER_TILE * TILES_PER_SQUARE;
    int pointj = mc.j - sc.j*POINTS_PER_PIXEL * PIXELS_PER_TILE * TILES_PER_SQUARE;
    
    float pixeli = (1.0 * pointi) / POINTS_PER_PIXEL;
    float pixelj = (1.0 * pointj) / POINTS_PER_PIXEL;
    
    sfVector2f position;
    position.x = pixelj;
    position.y = pixeli;
    
    sfSprite_setPosition(sprite, position);
    
    
    sfRenderTexture* Footprint = Ground_Surface->Footprints_Render_Texture;
    sfRenderTexture_drawSprite(Footprint, sprite, NULL);
    
    
    
    
    


}

int draw_skin(bbDrawable* tobedrawn, int i){

    //if no skin, do nothing: SKIN_NONE
    int skin_int = tobedrawn->skin;
    if (skin_int == SKIN_NONE) return 0;
    //if state not recognised, do nothing: state < 0 or state >= INNER_STATES_PER_SKIN

    int state = tobedrawn->state;
    if (state < 0 || state >= INNER_STATES_PER_SKIN) return 0;

    //lookup drawfunction from skin,
    // return either draw_once_skin() or repeatdraw_skin()


    int drawfunction_int = bbSkins[skin_int].drawfunctions_int[state][i];

    //printf("state = %d, drawfunction_int = %d\n",state, drawfunction_int);
    return bbDrawfunction_vtable[drawfunction_int](tobedrawn, i);
}

int treedraw(bbDrawable* tobedrawn, int i){

    int animation = tobedrawn->animation[i];
    int angle = tobedrawn->angle[i];
    int frame = tobedrawn->frame[i];

    bbMapCoords mc = tobedrawn->location;
    bbScreenCoords sc = bbMapCoords_getScreenCoords_centre(mc);

    //printf("x=%f, y=%f\n", sc.x, sc.y);

    sfVector2f position;
    position.x = sc.x;
    position.y = sc.y;

    sfSprite* sprite = bbAnimation_getSprite(animation,angle,frame);

    sfSprite_setPosition(sprite, position);
    sfRenderTexture_drawSprite(bbViewport_main, sprite, NULL);



    return 0;
}

int unitdraw(bbDrawable* tobedrawn, int i){

        int animation = tobedrawn->animation[i];


        int angle = tobedrawn->angle[i];
        int frame = tobedrawn->frame[i];

        bbMapCoords mc = tobedrawn->location;

        bbScreenCoords sc = bbMapCoords_getScreenCoords_centre(mc);

        sfVector2f position;
        position.x = sc.x;
        position.y = sc.y;


        sfSprite* sprite = bbAnimation_getSprite(animation, angle, frame);


        sfSprite_setPosition(sprite, position);
        sfRenderTexture_drawSprite(bbViewport_main, sprite, NULL);
        sfRenderTexture_drawSprite(bbViewport_highlights, sprite, NULL);

        bbAnimation* anim = bbAnimation_vtable[animation];

        int frames = anim->frames;
        int framerate = anim->framerate;

        tobedrawn->frame[i] = (frame+1)%(frames*framerate);

        return 0;
    }

int bbDrawfunction_initAll(){

    Circle = sfCircleShape_create();
    sfCircleShape_setFillColor(Circle, sfTransparent);
    sfCircleShape_setOutlineColor(Circle, sfCyan);
    sfCircleShape_setOutlineThickness(Circle, 2.0);
    
    

    bbDrawfunction_vtable[DRAW_BASIC] = basicdraw;
    bbDrawfunction_vtable[DRAW_NULL] = nulldraw;
    bbDrawfunction_vtable[DRAW_REPEAT] = repeatdraw;
    bbDrawfunction_vtable[DRAW_BALLOON] = balloondraw;
    bbDrawfunction_vtable[DRAW_SHADOW] = shadowdraw;
    bbDrawfunction_vtable[DRAW_REPEAT_SKIN] = repeatdraw_skin;
    bbDrawfunction_vtable[DRAW_ONCE_SKIN] = draw_once_skin;
    bbDrawfunction_vtable[DRAW_SKIN] = draw_skin;
    bbDrawfunction_vtable[DRAW_TREE] = treedraw;
    bbDrawfunction_vtable[DRAW_UNIT] = unitdraw;
    
    return 0;
}


