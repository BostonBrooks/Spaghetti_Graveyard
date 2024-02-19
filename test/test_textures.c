#include "../headers/textures.h"
#include "../headers/system_includes.h"

int main(void) {
	textures_load();

	bbDictionary_print(texture_dict);

	sfVideoMode mode = {800, 600, 32};
	sfRenderWindow* window;
	sfTexture* texture;
	sfSprite* sprite;

	window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
	if (!window)
		return EXIT_FAILURE;

	int texture_int = bbDictionary_lookup(texture_dict, "ETSY_TREES_1");

	printf("texture int = %d\n", texture_int);
	texture = sfTexture_vtable[texture_int];

	sprite = sfSprite_create();
	sfSprite_setTexture(sprite, texture, sfTrue);



	sfRenderWindow_clear(window, sfBlack);

	sfRenderWindow_drawSprite(window, sprite, NULL);

	sfRenderWindow_display(window);

	sleep(1);

	exit(1);


}