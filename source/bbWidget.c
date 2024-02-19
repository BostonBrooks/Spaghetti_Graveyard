#include "../headers/bbWidget.h"
#include "../headers/pools.h"
#include "../headers/flags.h"
#include "../headers/commands.h"
#include "../headers/sprites.h"

//include files for each widget
#include "../widgets/decal.h"
#include "../widgets/button.h"
#include "../widgets/menu.h"

int widget_mouseover;
int root_widget;
int selected_widget;

int (*bbWidget_Constructors[TBA])(bbScreenCoords screen_coords, int parent);
int (*bbWidget_DrawFunctions[TBA])(int self);
int (*bbWidget_Destructors[TBA])(int self);
int (*bbWidget_OnCommand[TBA])(int self, int command, void* data);


DEFINE_POOL(bbWidget, 500, 51)

int bbWidget_Draw(int widget_int){

	bbWidget* widget = bbWidget_Pool_Lookup(widget_int);

	if (widget->visible){
		bbWidget_DrawFunctions[widget->on_draw](widget_int);
	}

	return (F_SUCCESS);
}

int Widgets_Init(void){
	bbWidget_Constructors[W_DECAL]  = Decal_New;
	bbWidget_DrawFunctions[W_DECAL] = Decal_Draw;
	bbWidget_Destructors[W_DECAL]   = Decal_Delete;
	bbWidget_OnCommand[W_DECAL]     = Decal_OnCommand;

	bbWidget_Constructors[W_MENU_BUTTON]  = Button_New;
	bbWidget_DrawFunctions[W_MENU_BUTTON] = Button_Draw;
	bbWidget_Destructors[W_MENU_BUTTON]   = Button_Delete;
	bbWidget_OnCommand[W_MENU_BUTTON]     = Button_OnCommand;


	bbWidget_Constructors[W_MENU]  = Menu_New;
	bbWidget_DrawFunctions[W_MENU] = Menu_Draw;
	bbWidget_Destructors[W_MENU]   = Menu_Delete;
	bbWidget_OnCommand[W_MENU]     = Menu_OnCommand;

}

int Widgets_Create(void){
	bbScreenCoords  SC;
	SC.x = 0;
	SC.y = 0;
	return bbWidget_Constructors[W_DECAL](SC, F_NONE);
}