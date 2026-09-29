#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    int value;
} Dictionary;

char** getDictionaryKeys(Dictionary* dictionary, int size) {
    if (dictionary == NULL) return NULL;
    char** keys = (char**) calloc(size, sizeof(char*));
    if (keys == NULL) return NULL;
    for (int i = 0; i < size; i++) {
        if (dictionary[i].key != NULL) {
            keys[i] = strdup(dictionary[i].key);
            if (keys[i] == NULL) {
                for (int j = 0; j < i; j++)
                    free(keys[j]);
                free(keys);
                return NULL;
            }
        }
    }
    return keys;
}

int main() {
    int size = 3;
    Dictionary* dictionary = (Dictionary*)calloc(size, sizeof(Dictionary));
    if (dictionary) {
        dictionary[0].key = strdup("apple");
        dictionary[0].value = 10;
        dictionary[1].key = strdup("banana");
        dictionary[1].value = 5;
        dictionary[2].key = strdup("orange");
        dictionary[2].value = 7;

        char** keys = getDictionaryKeys(dictionary, size);
        if (keys) {
            for (int i = 0; i < size; i++) {
                if (keys[i]) {
                    printf("%s\n", keys[i]);
                    free(keys[i]);
                }
            }
            free(keys);
        }

        for (int i = 0; i < size; i++) {
            if (dictionary[i].key) {
                free(dictionary[i].key);
            }
        }
        free(dictionary);
    }
    return 0;
}