/**
 * @file
 *
 * @ingroup
 * @brief Everything drawn to the screen that is not part of the viewport is a widget.
 *        Every spell is it's own widget. click to select spell or type the spells code to do the same.
 */
#ifndef BBWIDGET_H
#define BBWIDGET_H

#include "../headers/constants.h"
#include "../headers/geometry.h"
#include "../headers/system_includes.h"
#include "../headers/pools.h"

extern int widget_mouseover; /** the current widget that is below the mouse pointer */
extern int root_widget; /** all other widgets belong to this widget, used to display decal */
extern int selected_widget; /** keypresses are sent to the selected widget? */

extern int (*bbWidget_Constructors[TBA])(bbScreenCoords screen_coords, int parent);
extern int (*bbWidget_DrawFunctions[TBA])(int self);
extern int (*bbWidget_Destructors[TBA])(int self);
extern int (*bbWidget_OnCommand[TBA])(int self, int command, void* data);

int bbWidget_Draw(int widget_int);
int Widgets_Init(void);
int Widgets_Create(void);

typedef struct {

	/** Stuff for storing widgets in a pool */
	int Pool_Self;
	int Pool_Prev;
	int Pool_Next;
	int Pool_In_Use;

	bbScreenCoords screen_coords;

	bool visible;
	bool subwidgets_visible;

	char* text;
	char* more_text;       /** display text on mouseover */
	char* command_prompt;  /** typing this code in the prompt is equivalent to clicking on it */
	char* sprite_label;    /** used to look up the sprite in a dictionary */
	int sprite_int;


	void* extra_data;

	int on_command;
	int on_draw;       /**< integer location of virtual function in vtable */
	int on_delete;     /**< integer location of virtual function in vtable */




	int parent_widget;

	int subwidget_head; /** start of linked list of widgets belonging to the current widget */
	int subwidget_tail; /** end of linked list of widgets belonging to the current widget */

	int widget_previous; /** used for list of subwidgets belonging to a higher widget */
	int widget_next;     /** used for list of subwidgets belonging to a higher widget */
} bbWidget;

DECLARE_POOL_GLOBALS(bbWidget, 500, 51)

// widget types
#define W_DECAL          0    //background colour
#define W_SPELL          1    //click to cast a spell/select active spell (an also be done using prompt)
#define W_DIOLOGUE       2    //display info on selected item
#define W_MINIMAP        3
#define W_MENU           4
#define W_MENU_BUTTON    5
#define W_PROMPT         6    //display previous command prompts and questions
#define W_TEXT_ENTRY     7    //enter command prompts and answers

// specific widgets



#endif // BBWIDGET_H