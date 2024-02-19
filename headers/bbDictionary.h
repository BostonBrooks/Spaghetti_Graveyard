/**
 * @file
 *
 * @ingroup
 * @brief enter a string and receive an integer
 * entries are stored in a pool of max size 10,000
 * entries are sorted into 157 buckets based on a hash function not unlike
 * the one found at http://www.cse.yorku.ca/~oz/hash.html
 * keys are strings such as a label given to a texture/sprite/animation
 * values are integers >= 0 (array indices)
 */

#ifndef BBDICTIONARY_H
#define BBDICTIONARY_H

#define NUM_BINS 11

typedef struct { // To be used for variable number of bins
	int head;
	int tail;
} head_tail;

typedef struct {

	int Dict_Self;
	int Dict_Prev;
	int Dict_Next;
	int Dict_In_Use;

	char key[33];
	int value;

} bbDictionary_entry;


typedef struct {


	bbDictionary_entry* Pool[100];

	int Dict_Available_Head;
	int Dict_Available_Tail;
	int Dict_In_Use_Head[NUM_BINS];
	int Dict_In_Use_Tail[NUM_BINS];



} bbDictionary;




bbDictionary* bbDictionary_new();
int bbDictionary_delete(bbDictionary* dict);
int bbDictionary_add(bbDictionary* dict, char* key, int value);  //and overwrite if duplicate
int bbDictionary_remove(bbDictionary* dict, char* key);
int bbDictionary_lookup(bbDictionary* dict, char* key);
int bbDictionary_clear(bbDictionary* dict);
int bbDictionary_print(bbDictionary* dict);



#endif // BBDICTIONARY_H