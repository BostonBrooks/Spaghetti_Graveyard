/**
 * @file
 *
 * @ingroup
 * @brief This is a singleton containing data about the game's main window.
 */
#ifndef BBWINDOW_H
#define BBWINDOW_H

#include "../headers/all_includes.h"

typedef struct {

    sfRenderWindow window;
    int width;
    int height;
    char title[128];

    int decal_int;   //TODO consolidate with root_widget
    bbViewport* viewport;
    bbPrompt* prompt;
    bbTextbox* textbox;
    int widgets_head;
    int widgets_tail;

} bbWindow;

/** create a bbWindow from constants found in constants.h */
int bbWindow_create_from_constants(bbWindow* window);

int bbWindow_distroy(bbWindow* window);

/** display everything */
int bbWindow_draw(bbWindow* window);

int bbWindow_poll_event(bbWindow* window);

#endif