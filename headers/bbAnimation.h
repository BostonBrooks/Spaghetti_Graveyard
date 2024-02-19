#ifndef BBANIMATION_H
#define BBANIMATION_H

#include "../headers/bbDictionary.h"
#include "../headers/system_includes.h"

typedef struct {

	char key[33];
	//int address;
	int Vdrawfunction;
	int angles;
	int frames;
	int framerate;  //should this be a float?
	int sprites[];

} bbAnimation;

extern bbAnimation** bbAnimation_vtable;
extern bbDictionary* animation_dict;

int animations_load();
int animations_free();
int animation_lookup(char* identifier);

sfSprite* bbAnimation_getSprite(int animation_int, int angle_int, int frame_int);

int animations_print();

#endif //BBANIMATION_H