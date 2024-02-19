/**
 * @file
 *
 * @ingroup
 * @brief The decal is the top-level widget. All other widgets belong to the decal, recursively.
 *        The decal is responsible for the window background and
 */

#ifndef DECAL_H
#define DECAL_H

#include "../headers/constants.h"
#include "../headers/geometry.h"
#include "../headers/system_includes.h"
#include "../headers/pools.h"
#include "../headers/bbWidget.h"
#include "../headers/media.h"
#include "../headers/window.h"

int Decal_New (bbScreenCoords screen_coords, int parent){
	//look up decal sprite
	//set screen coords to 0,0
	// root widget is set based on the return value of this function

	int widget_int = bbWidget_Pool_New(NEXT_AVAILABLE);
	assert (widget_int >= 0);
	bbWidget* widget = bbWidget_Pool_Lookup(widget_int);

	widget->parent_widget = F_NONE;
	widget->screen_coords.x = 0;
	widget->screen_coords.y = 0;


	widget->visible = true;
	widget->subwidgets_visible = true;

	widget->text = "this is the decal widget\n"; //im not sure if this is how we set the value of char*

	if (RESOLUTION == 1920)	widget->sprite_label = "DECAL1920";

	//TODO - Look up label in dictionary / generate decal based on unusual screen coords
	widget->sprite_int = DECAL_INT;

	widget->extra_data = NULL;

	widget->on_draw = W_DECAL;
	widget->on_delete = W_DECAL;
	widget->on_command = F_NONE;

	widget->subwidget_head = -1;   //initialised with no subwidgets
	widget->subwidget_tail = -1;

	widget->widget_previous = -1;  //initialised not belonging to any widgets
	widget->widget_next = -1;

	widget_int;
    printf("Create new Decal.\n");

	//initilaise subwidgets

	bbScreenCoords  SC;
	SC.x = 350;
	SC.y = 80;
	bbWidget_Constructors[W_MENU](SC, widget_int);

	return widget_int;
}

int Decal_Delete (int self){
	//call delete on sub-widgets
	//free data
}

int Decal_Draw(int self){
	bbWidget* widget = bbWidget_Pool_Lookup(self);
	sfVector2f position;
	position.x = widget->screen_coords.x;
	position.y = widget->screen_coords.y;
	sfSprite* sprite = sfSprite_vtable[widget->sprite_int];
	sfSprite_setPosition(sprite, position);
	sfRenderWindow_drawSprite(window, sprite,NULL);

	int subwidget_int = widget->subwidget_head;

	while(subwidget_int != -1){
		bbWidget_Draw(subwidget_int);
		bbWidget* subwidget = bbWidget_Pool_Lookup(subwidget_int);
		subwidget_int = subwidget->widget_next;

	}

}

int Decal_OnCommand(int self, int command, void* data){

	switch (command){
		case C_REFRESH_GRAPHICS:
			//change sprite_int after reloading media
			break;
	}

}
#endif // DECAL_H