#include "../headers/system_includes.h"

#include "../headers/textures.h"
#include "../headers/sprites.h"
#include "../headers/bbAnimation.h"

int main (void){
	printf ("Program runs!\n");

	textures_load();
	sprites_load();
	animations_load();

	printf("Program runs without errors!");
}