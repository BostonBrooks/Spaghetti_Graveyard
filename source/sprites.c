#include "../headers/bbDictionary.h"
#include "../headers/system_includes.h"
#include "../headers/textures.h"
#include "../headers/flags.h"
#include "../headers/sprites.h"
#include "../headers/constants.h"

sfSprite** sfSprite_vtable;
bbDictionary* sprite_dict;

int sprites_load();
int sprites_free();
int sprite_lookup(char* identifier);
int sprite_load(char* key, int address, char* texture, int left, int top, int width,
				int height, float originx, float originy, float scalex, float scaley);

int sprites_load(){
	sprite_dict = bbDictionary_new();

    sfSprite_vtable = (sfTexture**) calloc (TBA_LARGE, sizeof (sfSprite*));
	assert(sfSprite_vtable != NULL);

	FILE* sprites_file = fopen("../maps/map0/sprites.csv", "r");
	assert(sprites_file != NULL);

	int flag = fscanf(sprites_file, "Label:,Virtual Address:,sfTexture:,Left:,Top:,Width:,Height:,Origin_X:,Origin_Y:,Scale_X:,Scale_Y:,Comment:\n");
	assert(flag == 0);

	char key[33];
	int address;
	char texture[33];
	int left, top, width, height;
	float originx, originy;
	float scalex, scaley;

	while((flag = fscanf(sprites_file,"%[^,],%d,%[^,],%d,%d,%d,%d,%f,%f,%f,%f",
								 key, &address, texture, &left, &top, &width, &height,
								 &originx, &originy, &scalex, &scaley))==11){
		fscanf(sprites_file,"%*[^\n]\n");

		sprite_load(key, address, texture, left, top, width, height, originx, originy, scalex, scaley);
	}

	fclose(sprites_file);

	return F_SUCCESS;

}

int sprite_lookup(char* identifier){
	//identifier is either an ascii coded integer or a hashtable key
	int len = strlen(identifier);
	char digits[] = "0123456789";
	int int_len = strspn(identifier,digits);
	if (len == int_len) return atoi(identifier);

	return bbDictionary_lookup(sprite_dict, identifier);

}

int sprite_load(char* key, int address, char* texture, int left, int top, int width,
				int height, float originx, float originy, float scalex, float scaley){

	sfSprite* New_Sprite = sfSprite_create();

	int texture_address = texture_lookup(texture);

	//printf("texture = %s, texture address = %d\n", texture, texture_address);

	sfSprite_setTexture(New_Sprite, sfTexture_vtable[texture_address], sfTrue);

	sfIntRect rectangle;

	rectangle.left = left;
	rectangle.top = top;
	rectangle.width = width;
	rectangle.height = height;

	sfSprite_setTextureRect(New_Sprite, rectangle);

	sfVector2f origin;

	origin.x = originx;
	origin.y = originy;

	sfSprite_setOrigin(New_Sprite, origin);

	sfVector2f scale;
	scale.x = scalex;
	scale.y = scaley;

	sfSprite_setScale(New_Sprite, scale);

	sfSprite_vtable[address] = New_Sprite;

	bbDictionary_add(sprite_dict, key, address);

	return F_SUCCESS;
}


