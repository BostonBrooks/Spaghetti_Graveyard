#include "../headers/bbWidget.h"
#include "../headers/constants.h"
#include "../headers/window.h"
#include "../headers/system_includes.h"
#include "../headers/flags.h"

int main(void){

	textures_load();
	sprites_load();
	animations_load();
	//create window
	Window_Init();

	sfRenderWindow_display(window);
	//populate function vtables

    Widgets_Init();

	//create widgets

	Widgets_Create();

	while(1){
		//get mouse

		//draw widgets

		sfRenderTexture_clear(window, sfRed);

		bbWidget_Draw(root_widget);

		sfRenderWindow_display(window);
	}

}