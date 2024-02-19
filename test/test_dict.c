#include "../headers/bbDictionary.h"
#include "../headers/flags.h"

int main (void){

	bbDictionary* dict = bbDictionary_new();
	char input_str[33];
	int input_int;
	char ouptut_int;


	while (1){

		printf("enter new key and value\n");

		scanf("%s %d", input_str, &input_int);

		bbDictionary_add(dict, input_str, input_int);
		bbDictionary_print(dict);
		printf("look up a key\n");

		scanf("%s", input_str);

		ouptut_int = bbDictionary_lookup(dict, input_str);

		if (ouptut_int == F_NONE) {
			printf("key not found\n");
		} else {
			printf("%s %d\n", input_str, ouptut_int);
		}
	}


}