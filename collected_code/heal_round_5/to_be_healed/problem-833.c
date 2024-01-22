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
    char** keys = (char**) calloc(size, sizeof(char*));
    if (keys == NULL)
        return NULL;
    for (int i = 0; i < size; i++) {
        if (dictionary[i].key != NULL) {
            keys[i] = strdup(dictionary[i].key);
        }
    }
    return keys;
}

int main() {
    int num_items = 3;
    Dictionary* dictionary = (Dictionary*)calloc(num_items, sizeof(Dictionary));
    if (dictionary) {
        dictionary[0].key = strdup("apple");
        dictionary[0].value = 10;
        dictionary[1].key = strdup("banana");
        dictionary[1].value = 5;
        dictionary[2].key = strdup("orange");
        dictionary[2].value = 7;

        int size = num_items;
        char** keys = getDictionaryKeys(dictionary, size);
        if (keys != NULL) {
            for (int i = 0; i < size; i++) {
                if (keys[i] != NULL) {
                    printf("%s\n", keys[i]);
                    free(keys[i]);
                }
            }
            /* Possible weaknesses found:
             *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
             */
            free(keys);
        }

        for (int i = 0; i < num_items; i++) {
            if (dictionary[i].key != NULL) {
                free(dictionary[i].key);
            }
        }
        free(dictionary);
    }
    return 0;
}