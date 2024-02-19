
#include "../headers/constants.h"
#include "../headers/geometry.h"
#include "../headers/system_includes.h"
#include "../headers/pools.h"
#include "../headers/bbWidget.h"
#include "../headers/media.h"
#include "../headers/window.h"

int Menu_New(bbScreenCoords screen_coords, int parent){

	printf("Create new menu.\n");

	int widget_int = bbWidget_Pool_New(NEXT_AVAILABLE);
	assert (widget_int >= 0);
	bbWidget* widget = bbWidget_Pool_Lookup(widget_int);


	widget->screen_coords.x = screen_coords.x;
	widget->screen_coords.y = screen_coords.y;

    widget->visible = true;
	widget->subwidgets_visible = true;

	widget->text = "Menu";
	widget->sprite_label = "MENU_1920";

	widget->sprite_int = sprite_lookup(widget->sprite_label);

	widget->extra_data = NULL;

	widget->on_draw = W_MENU;
	widget->on_delete = W_MENU;
	widget->on_command = W_MENU;

	widget->subwidget_head = -1;   //initialised with no subwidgets
	widget->subwidget_tail = -1;

	widget->widget_previous = -1;  //initialised not belonging to any widgets
	widget->widget_next = -1;

	bbWidget* parent_widget = bbWidget_Pool_Lookup(parent);

	//Add to parent widget's subwidget list;
	widget->parent_widget = parent;

	if (parent_widget->subwidget_head == -1){
		assert(parent_widget->subwidget_tail == -1);

		parent_widget->subwidget_head = widget_int;
		parent_widget->subwidget_tail = widget_int;

		widget->widget_previous = -1;
		widget->widget_next = -1;
	} else {
		assert(parent_widget->subwidget_tail != -1);

		widget->widget_previous = parent_widget->subwidget_tail;
		widget->widget_next = -1;

		bbWidget* widget_previous = bbWidget_Pool_Lookup(parent_widget->subwidget_tail);

		widget_previous->widget_next = widget_int;
		parent_widget->subwidget_tail = widget_int;

	}


	//initialise subwidgets
	bbScreenCoords  SC;
	SC.x = 0;
	SC.y = 0;
	bbWidget_Constructors[W_MENU_BUTTON](SC, widget_int);

	//add subwidget to subwidgets list

	return widget_int;
}

int Menu_Draw(int self){
	bbWidget* widget = bbWidget_Pool_Lookup(self);
	sfVector2f position;
	position.x = widget->screen_coords.x;
	position.y = widget->screen_coords.y;
	sfSprite* sprite = sfSprite_vtable[widget->sprite_int];
	sfSprite_setPosition(sprite, position);
	sfRenderWindow_drawSprite(window, sprite, NULL);

	int subwidget_int = widget->subwidget_head;

	while(subwidget_int != -1){
		bbWidget_Draw(subwidget_int);
		bbWidget* subwidget = bbWidget_Pool_Lookup(subwidget_int);
		subwidget_int = subwidget->widget_next;

	}

	return F_NONE;
}

int Menu_Delete(int self){
	return F_NONE;
}

int Menu_OnCommand(int self, int command, void* data){
	return F_NONE;
}