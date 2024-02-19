#include <stdio.h>
#include <stdlib.h>
#include "../headers/system_includes.h"
#include "../headers/bbDictionary.h"
#include "../headers/flags.h"
#include "../headers/constants.h"

sfTexture** sfTexture_vtable;

int textures_load();
int textures_free();

bbDictionary* texture_dict;

int texture_lookup(char* identifier);

int texture_load(char* key, int address, char* file, sfBool smooth);



int textures_load(){

	texture_dict = bbDictionary_new();


	sfTexture_vtable = (sfTexture**) calloc (TBA_LARGE, sizeof (sfTexture*));
	assert(sfTexture_vtable != NULL);

	FILE* textures_file = fopen("../maps/map0/textures.csv", "r"); //STUB: this should not be hard-coded
	assert(textures_file != NULL);

	int flag = fscanf(textures_file, "Label:,Virtual Address:,File:,Smooth:,Comment:\n");

	assert(flag == 0);

	char key[33];
	int address;
	char file[129];
	char Smooth;

	//printf("Label:,Virtual Address:,File:,Smooth:,Comment:\n");
	while((flag = fscanf(textures_file, "%[^,],%d,%[^,],%c", key,&address,file, &Smooth)) == 4){
		fscanf(textures_file,"%*[^\n]\n");

		if(Smooth == 'T'){
			texture_load(key, address, file, sfTrue);
		} else {
			texture_load(key, address, file, sfFalse);
		}
	}

	fclose(textures_file);
	return F_SUCCESS;
}

int texture_load(char* key, int address, char* file, sfBool smooth){
	//printf("%s, %d, %s, %c\n", key, address, file, (smooth == sfTrue) ? 'T' : 'F' );

	sfTexture* new_texture = sfTexture_createFromFile(file, NULL);
	sfTexture_setSmooth(new_texture, smooth);

	sfTexture_vtable[address] = new_texture;

	bbDictionary_add(texture_dict, key, address);
	//printf("%s\n", key);
	return F_SUCCESS;
}

int texture_lookup(char* identifier){
    //identifier is either an ascii coded integer or a hashtable key
	int len = strlen(identifier);
	char digits[] = "0123456789";
	int int_len = strspn(identifier,digits);
	if (len == int_len) return atoi(identifier);

	//what if the result of atoi is too large?

	return bbDictionary_lookup(texture_dict, identifier);

}