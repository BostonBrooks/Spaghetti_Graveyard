

/**
 * @file
 *
 * @ingroup 
 * @brief Contains shaders and textures for drawing to the viewport
 */
#ifndef VIEWPORT_H
#define VIEWPORT_H


//-----------------------------INCLUDES----------------------------//

#include "../headers/system_includes.h"
#include "../headers/constants.h"
#include "../headers/media.h"
#include "../headers/window.h"

//-----------------------------CONSTANTS----------------------------//

//Constants may be found in constants.h

//-----------------------------STRUCURES------------------------------//



//-----------------------------GLOBALS----------------------------//

extern sfRenderTexture* viewport; //deprecated/dummy texture
extern sfTexture* viewport_texture;
extern sfSprite* viewport_sprite;



extern sfRenderTexture* bbViewport_background;
extern sfTexture* bbViewport_background_texture;
extern sfSprite* bbViewport_background_sprite;


extern sfRenderTexture* bbViewport_ground;
extern sfTexture* bbViewport_ground_texture;
extern sfSprite* bbViewport_ground_sprite;


extern sfRenderTexture* bbViewport_main;
extern sfTexture* bbViewport_main_texture;
extern sfSprite* bbViewport_main_sprite;


extern sfRenderTexture* bbViewport_highlights;
extern sfTexture* bbViewport_highlights_texture;
extern sfSprite* bbViewport_highlights_sprite;


extern sfRenderTexture* bbViewport_healthbars;
extern sfTexture* bbViewport_healthbars_texture;
extern sfSprite* bbViewport_healthbars_sprite;


extern sfRenderStates bbViewport_renderer; 
extern sfShader* bbViewport_shader;

//-----------------------------FUNCTIONS--------------------------//

/** Create shaders for drawing drawables to viewport */
int bbViewport_shaders_create (void);

/** Create textures for drawing to the viewport */
int bbViewport_init(void);

#endif
