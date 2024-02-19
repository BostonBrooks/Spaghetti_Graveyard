#include "../headers/bbAnimation.h"
#include <string.h>
#include "../headers/bbDictionary.h"
#include "../headers/flags.h"
#include "../headers/constants.h"
#include "../headers/textures.h"
#include "../headers/sprites.h"
#include "../headers/system_includes.h"

bbAnimation** bbAnimation_vtable;
bbDictionary* animation_dict;

int animations_load();
int animations_free();
int animation_lookup(char* identifier);

sfSprite* bbAnimation_getSprite(int animation_int, int angle_int, int frame_int);


int animations_load(){

	animation_dict = bbDictionary_new();

	bbAnimation_vtable = (bbAnimation**) calloc (TBA_LARGE, sizeof (bbAnimation*));
	assert(bbAnimation_vtable != NULL);

	FILE* animation_file = fopen("../maps/map0/animations.csv", "r");
	assert(animation_file != NULL);

	char key[33];
	int address;
	int drawfunction;
	int angles;
	int frames;
	int framerate;
	int sprites[TBA_LARGE];

	int flag = fscanf(animation_file, "Label:,V_Address:,V_DrawFunction:,Angles:,Frames:,Framerate:,Sprites[]");
	assert(flag == 0);
	fscanf(animation_file,"%*[^\n]\n");

	while((flag = fscanf(animation_file,"%[^,],%d,%d,%d,%d,%d", key, &address, &drawfunction, &angles, &frames, &framerate ))==6){
        //printf("animation key = %s\n", key);
		for(int i = 0; i < angles * frames; i++){
			char sprite_key[33] = "bad fscanf";
			flag = fscanf(animation_file, ",%[^,]", sprite_key);
			//assert(flag == 1);

			int sprite_index = sprite_lookup(sprite_key);


			sprites[i] = sprite_index;

			//printf("key = %s, index = %d\n", sprite_key, sprite_index);

		}

		fscanf(animation_file, "%*[^\n]\n");
		animation_load(key, address, drawfunction, angles, frames, framerate, sprites);

	}

	fclose(animation_file);
	return F_SUCCESS;
}

int animation_load(char* key, int address, int drawfunction, int angles, int frames, int framerate, int sprites[]){
//	printf("key = %s, address = %d, VDrawfunction = %d, angles = %d, frames = %d, framerate = %d, sprites[]",
//		   key, address, drawfunction, angles, frames, framerate);
//
//	for (int i = 0; i< angles * frames; i++){
//		printf(" %d,", sprites[i]);
//	}
//
//	printf("\n");

	bbAnimation* animation = malloc (sizeof(bbAnimation) + sizeof(int) * angles * frames);
	assert(animation != NULL);

	strcpy(animation->key, key);
	animation->Vdrawfunction = drawfunction;
	animation->angles = angles;
	animation->frames = frames;
	animation->framerate = framerate;

	for(int i = 0; i < angles * frames; i++){
		animation->sprites[i] = sprites[i];
	}

	bbAnimation_vtable[address] = animation;

	bbDictionary_add(animation_dict,key,address);

	return F_SUCCESS;
}

int animation_lookup(char* identifier){
	//identifier is either an ascii coded integer or a hashtable key
	int len = strlen(identifier);
	char digits[] = "0123456789";
	int int_len = strspn(identifier,digits);
	if (len == int_len) return atoi(identifier);

	return bbDictionary_lookup(animation_dict, identifier);

}


sfSprite* bbAnimation_getSprite(int animation_int, int angle_int, int frame_int){
//TODO test for non-negative inputs
	bbAnimation* animation = bbAnimation_vtable[animation_int];
	int sprite_int = (animation->frames)*angle_int + frame_int/animation->framerate;
	int sprite_num = animation->sprites[sprite_int];


//TODO why do we get a -1 here?

    //printf("sprite num = %d, animation_int = %d, angle_int = %d, frame_int = %d\n", sprite_num, animation_int, angle_int, frame_int);

	if (sprite_num == -1) return sfSprite_vtable[44];
	return sfSprite_vtable[sprite_num];

}

int animation_print(int animation_int){


	bbAnimation* animation = bbAnimation_vtable[animation_int];

	if (animation != 0) {

		printf("key = %s, address = %d, VDrawfunction = %d, angles = %d, frames = %d, framerate = %d, sprites[]",
			   animation->key, animation_int, animation->Vdrawfunction, animation->angles, animation->frames, animation->framerate);
        for(int i = 0; i < animation->angles * animation->frames; i++){
			printf(" %d,", animation->sprites[i]);
		}
		printf("\n");
	}

}

int animations_print(){
	for(int i = 0; i < TBA_LARGE; i++){
		animation_print(i);
	}
}
