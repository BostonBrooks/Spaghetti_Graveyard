#include "../headers/textures.h"
#include "../headers/sprites.h"
#include "../headers/system_includes.h"

int main(void) {
	textures_load();
	sprites_load();

	bbDictionary_print(sprite_dict);

	sfVideoMode mode = {800, 600, 32};
	sfRenderWindow* window;
	sfSprite* sprite;

	window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
	if (!window)
		return EXIT_FAILURE;

	int sprite_int = bbDictionary_lookup(sprite_dict, "TREE_1");


    printf("sprite_int = %d\n", sprite_int);

	assert(sprite_int >= 0);

	sprite = sfSprite_vtable[sprite_int];

	sfVector2f position;

	position.x = 300;
	position.y = 400;

	sfSprite_setPosition(sprite, position);

	sfRenderWindow_clear(window, sfBlack);

	sfRenderWindow_drawSprite(window, sprite, NULL);

	sfRenderWindow_display(window);

	sleep(5);

	exit(1);


}