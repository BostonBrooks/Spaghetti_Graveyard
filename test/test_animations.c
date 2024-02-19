#include "../headers/textures.h"
#include "../headers/sprites.h"
#include "../headers/bbAnimation.h"
#include "../headers/system_includes.h"

int main (void){

	textures_load();
	sprites_load();
	animations_load();

	//bbDictionary_print(animation_dict);
//printf("\n");

	//animations_print();
	//printf("\n");


	sfVideoMode mode = {800, 600, 32};
	sfRenderWindow* window;
	sfSprite* sprite;

	window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
	if (!window)
		return EXIT_FAILURE;
	sfRenderWindow_setFramerateLimit(window, 20);

	int animation_int = animation_lookup("Tree");

	//printf("animaiton int = %d\n", animation_int);

	for (int i = 0; i<50; i++) {
		sprite = bbAnimation_getSprite(animation_int, i, 0);


		sfVector2f position;

		position.x = 300;
		position.y = 500;

		sfSprite_setPosition(sprite, position);

		sfRenderWindow_clear(window, sfBlack);

		sfRenderWindow_drawSprite(window, sprite, NULL);

		sfRenderWindow_display(window);


	}
	exit(1);



}