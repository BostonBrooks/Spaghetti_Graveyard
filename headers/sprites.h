#ifndef SPRITES_H
#define SPRITES_H


#include "../headers/bbDictionary.h"
#include "../headers/system_includes.h"

extern sfSprite** sfSprite_vtable;

extern bbDictionary* sprite_dict;

int sprites_load();
int sprites_free();

int sprite_lookup(char* identifier);

#endif // SPRITES_H