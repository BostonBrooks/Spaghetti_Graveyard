/**
 * @file
 *
 * @ingroup
 * @brief Load textures from disk
 */
#ifndef TEXTURES_H
#define TEXTURES_H
#include "../headers/system_includes.h"
#include "../headers/bbDictionary.h"

extern sfTexture** sfTexture_vtable;

extern bbDictionary* texture_dict;

int textures_load();
int textures_free();

int texture_lookup(char* identifier);

#endif //TEXTURES_H