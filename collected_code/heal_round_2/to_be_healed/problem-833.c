#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    int value;
} Dictionary;

char** getDictionaryKeys(Dictionary* dictionary, int size) {
    if (dictionary == NULL) 
        return NULL;
    
    char** keys = (char**) malloc(size * sizeof(char*));
    if (keys == NULL)
        return NULL;
    
    for (int i = 0; i < size; i++) {
        keys[i] = strdup(dictionary[i].key);
    }
    return keys;
}

int main() {
    int num_items = 3;
    Dictionary* dictionary = (Dictionary*)malloc(num_items * sizeof(Dictionary));

    if (dictionary != NULL)
    {
 /* Possible weaknesses found:
  *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused). Risk is low because the source is a constant string.
  *  use of uninitialized value '*dictionary.key' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
  */
	strcpy(dictionary[0].key, "apple");
        dictionary[0].value = 10;

        /* Possible weaknesses found:
         *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused). Risk is low because the source is a constant string.
         */
        strcpy(dictionary[1].key, "banana");
        dictionary[1].value = 5;

        /* Possible weaknesses found:
         *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused). Risk is low because the source is a constant string.
         */
        strcpy(dictionary[2].key, "orange");
        dictionary[2].value = 7;
	
	int size = num_items;
	char** keys = getDictionaryKeys(dictionary, size);

	if (keys != NULL)
	{
	    for (int i = 0; i < size; i++) {
		printf("%s\n", keys[i]);
		free(keys[i]);
	    }
	    free(keys);
	}
	free(dictionary);
    }

    return 0;
}