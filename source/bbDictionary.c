#include "../headers/bbDictionary.h"
#include "../headers/flags.h"

#include <assert.h>
#include <string.h>
#include <stdint.h>

int hash(unsigned char *str)
{

	uint32_t hash_value = 5381;
	int i = 0;
	int c = str[i];

	while (c != '\0' && c!= '\n') {
		hash_value = hash_value * 33 + c;
		i++;
		c = str[i];

	}

	hash_value %= NUM_BINS;
	return hash_value;
}

bbDictionary* bbDictionary_new (){
	bbDictionary* dict = malloc(sizeof(bbDictionary)); //sizeof (bbDictionary) + 2*sizeof (int) * NUM_BINS;?
	assert( dict!= NULL);

	dict->Dict_Available_Head = F_NONE;
	dict->Dict_Available_Tail = F_NONE;

	for(int i = 0; i < NUM_BINS; i++){
		dict->Dict_In_Use_Head[i] = F_NONE;
		dict->Dict_In_Use_Tail[i] = F_NONE;
	}

	for (int i = 0; i < 100; i++){
		dict->Pool[i] = NULL;
	}

	return dict;
}

int bbDictionary_printHeadTail(bbDictionary* dict){
	printf("available head = %d, available tail = %d\n", dict->Dict_Available_Head, dict->Dict_Available_Tail);

	for (int i = 0; i < NUM_BINS; i++){
        printf("bin %d, head = %d, tail = %d\n", i, dict->Dict_In_Use_Head[i], dict->Dict_In_Use_Tail[i]);
	}

	printf("\n");

    return F_SUCCESS;
}

int bbDictionary_delete(bbDictionary* dict){
	for (int i = 0; i < 100; i++){
		if (dict->Pool[i] != NULL) free (dict->Pool[i]);
	}

	free(dict);
}

int bbDictionary_increase(bbDictionary* dict){
	int i = 0;
	while (dict->Pool[i] != NULL && i < 100) {
		i++;
	}
	if (i == 100) {
		return F_FULL;
	}

	bbDictionary_entry* entry = calloc(100, sizeof(bbDictionary_entry));
	assert(entry != NULL);
	dict->Pool[i] = entry;


	if (dict->Dict_Available_Head == F_NONE){
		assert(dict->Dict_Available_Tail == F_NONE);

		for (int l = 0; l < 100; l++){
			dict->Pool[i][l].Dict_Self = i * 100 + l;
			dict->Pool[i][l].Dict_Prev = i * 100 + l - 1;
			dict->Pool[i][l].Dict_Next = i * 100 + l + 1;
			dict->Pool[i][l].Dict_In_Use = 0;

		}


		dict->Pool[i][0].Dict_Prev = F_NONE;\
        dict->Pool[i][100 - 1].Dict_Next = F_NONE;\


		dict->Dict_Available_Head = i * 100;\
        dict->Dict_Available_Tail = (i+1) * 100 - 1;\

		return F_SUCCESS;
	}

	printf("Why are you increasing the pool when it's not empty?\n");
}

bbDictionary_entry* bbDictionary_index_lookup(bbDictionary* dict, int index){
	int level1 = index / 100;
	int level2 = index % 100;
	bbDictionary_entry* entry = &dict->Pool[level1][level2];
	assert (entry != NULL);
	//printf("index = %d, self = %d\n", index, entry->Dict_Self);
	return entry;
}


int bbDictionary_lookup_index(bbDictionary* dict, char* key){
	int hash_value = hash(key);

	int head = dict->Dict_In_Use_Head[hash_value];
	int tail = dict->Dict_In_Use_Tail[hash_value];

	int index = head;

	bbDictionary_entry* entry;

	while (index != F_NONE) {
		entry = bbDictionary_index_lookup(dict, index);
		if(strcmp(key, entry->key) == 0) return index;
		index = entry->Dict_Next;
	}

	return F_NONE;
}

int bbDictionary_lookup(bbDictionary* dict, char* key){
	int index = bbDictionary_lookup_index(dict, key);
	if (index == F_NONE) return F_NONE;
	bbDictionary_entry* entry = bbDictionary_index_lookup(dict, index);
	return entry->value;
}

bbDictionary_entry* grab_entry (bbDictionary* dict){ //remove an entry from available list and return

	if (dict->Dict_Available_Head == F_NONE){
		assert(dict->Dict_Available_Tail == F_NONE);
		bbDictionary_increase(dict);
	}

	if (dict->Dict_Available_Head == dict->Dict_Available_Tail) {
		bbDictionary_entry* entry = bbDictionary_index_lookup(dict, dict->Dict_Available_Head);


		dict->Dict_Available_Head = F_NONE;
		dict->Dict_Available_Tail = F_NONE;

		entry->Dict_Next = F_NONE;
		entry->Dict_Prev = F_NONE;
		entry->Dict_In_Use = 1;

		return entry;

	}

    bbDictionary_entry* entry = bbDictionary_index_lookup(dict, dict->Dict_Available_Head);
	dict->Dict_Available_Head = entry->Dict_Next;
	bbDictionary_entry* next_entry = bbDictionary_index_lookup(dict, entry->Dict_Next);
	next_entry->Dict_Prev = F_NONE;

	entry->Dict_Next = F_NONE;
	entry->Dict_Prev = F_NONE;
	entry->Dict_In_Use = 1;

	return entry;
}

int bbDictionary_add(bbDictionary* dict, char* key, int value){
	int hash_value = hash(key);
	int head = dict->Dict_In_Use_Head[hash_value];
	int tail = dict->Dict_In_Use_Tail[hash_value];
	bbDictionary_entry* entry;

    //printf("head == %d\n", head);

	//if bucket is empty, add to bucket.

	if (head == F_NONE){
		assert (tail == F_NONE);

		entry = grab_entry(dict);


		strcpy(entry->key, key);
		entry->value = value;


		dict->Dict_In_Use_Head[hash_value] = entry->Dict_Self;
		dict->Dict_In_Use_Tail[hash_value] = entry->Dict_Self;

		entry->Dict_Prev = F_NONE;
		entry->Dict_Next = F_NONE;
		//bbDictionary_printHeadTail(dict);
		return F_SUCCESS;
	}

	//printf("hash value = %d\n", hash_value);
	//bbDictionary_printHeadTail(dict);
	assert(dict->Dict_In_Use_Tail[hash_value] != F_NONE);
	//is the key already in use?
	int index = head;

	while (index != F_NONE){
		//printf("index = %d\n", index);
		entry = bbDictionary_index_lookup(dict, index);
		//if (entry == NULL) printf("entry == NULL\n");
		//if (key == NULL) printf("key = NULL\n");
		//if (entry->key == NULL) printf("entry->key = NULL\n");
		if (strcmp(key, entry->key) == 0) {
			entry->value = value;

			//bbDictionary_printHeadTail(dict);
			return F_SUCCESS;
		};
		index = entry->Dict_Next;
	}

	// if not, add to end of list

	entry = grab_entry(dict);
	entry->value = value;

	strcpy(entry->key, key);

	bbDictionary_entry* prev_entry = bbDictionary_index_lookup(dict, dict->Dict_In_Use_Tail[hash_value]);
	prev_entry->Dict_Next = entry->Dict_Self;
	entry->Dict_Prev = prev_entry->Dict_Self;

	dict->Dict_In_Use_Tail[hash_value] = entry->Dict_Self;
	entry->Dict_Next = F_NONE;

	//bbDictionary_printHeadTail(dict);
	return F_SUCCESS;
}

int bbDictionary_print(bbDictionary* dict){
	for (int i = 0; i < NUM_BINS; i++){
		printf("\nBin # %d:\n", i);
		printf("Dict_Self,\tDict_Prev,\tDict_Next,\tDict_In_Use,\tkey,\tvalue\n");
		int index = dict->Dict_In_Use_Head[i];
		while (index != F_NONE){
			bbDictionary_entry* entry = bbDictionary_index_lookup(dict, index);

			printf("%d\t\t%d\t\t%d\t\t%d\t\t%s\t\t%d\n",
				   entry->Dict_Self,
				   entry->Dict_Prev,
				   entry->Dict_Next,
				   entry->Dict_In_Use,
				   entry->key,
				   entry->value);

			index = entry->Dict_Next;
		}
	}
	printf("\n");
return F_SUCCESS;

	printf("\nAvailable:\n");
	printf("Dict_Self,\tDict_Prev,\tDict_Next,\tDict_In_Use,\tkey,\tvalue\n");
	int index = dict->Dict_Available_Head;
	while (index != F_NONE){
		bbDictionary_entry* entry = bbDictionary_index_lookup(dict, index);

		printf("%d\t\t%d\t\t%d\t\t%d\t\t%s\t\t%d\n",
			   entry->Dict_Self,
			   entry->Dict_Prev,
			   entry->Dict_Next,
			   entry->Dict_In_Use,
			   entry->key,
			   entry->value);

		index = entry->Dict_Next;
	}
}

/*
int bbDictionary_remove(bbDictionary* dict, char* key){
	int index = bbDictionary_lookup_index(dict, key);
	if (index == F_NONE) return F_NONE;

	bbDictionary_entry* entry = bbDictionary_index_lookup(dict, index);

	assert (entry->Dict_In_Use == 1);

	//remove from in use list

	if (entry->Dict_Prev == F_NONE && entry->Dict_Next == F_NONE){
		assert(dict->Dict_In_Use_Head == index);
		assert(dict->Dict_In_Use_Tail == index);
		dict->Dict_In_Use_Head = F_NONE;
		dict->Dict_In_Use_Tail = F_NONE;
	} else if (entry->Dict_Prev == F_NONE){
		assert(dict->Dict_In_Use_Head == index);
		dict->Dict_In_Use_Head = entry->Dict_Next;

		bbDictionary_entry* Next = bbDictionary_index_lookup(dict, entry->Dict_Next);
		Next->Dict_Prev = F_NONE;
	} else if (entry->Dict_Next == F_NONE){
		assert(dict->Dict_In_Use_Tail == index);
		dict->Dict_In_Use_Tail = entry->Dict_Prev;

		bbDictionary_entry* Prev = bbDictionary_index_lookup(dict, entry->Dict_Prev);
		Prev->Dict_Prev = F_NONE;
	} else {
		bbDictionary_entry* Prev = bbDictionary_index_lookup(dict, entry->Dict_Prev);
		bbDictionary_entry* Next = bbDictionary_index_lookup(dict, entry->Dict_Next);

		Prev->Dict_Next = entry->Dict_Next;
		Next->Dict_Prev = entry->Dict_Prev;
	}

	// add to available list

	entry->Dict_In_Use = 0;

	if (dict->Dict_Available_Head == F_NONE){
		assert(dict->Dict_In_Use_Tail == F_NONE);

		dict->Dict_Available_Head = index;
		dict->Dict_In_Use_Tail = index;

		entry->Dict_Prev = F_NONE;
		entry->Dict_Next = F_NONE;
	} else {
		entry->Dict_Next = F_NONE;
		entry->Dict_Next = dict->Dict_Available_Head;
		bbDictionary_entry* Head = bbDictionary_index_lookup(dict, dict->Dict_Available_Head);
		Head->Dict_Prev = index;
		dict->Dict_Available_Head = index;
	}

	return F_SUCCESS;
}
 */