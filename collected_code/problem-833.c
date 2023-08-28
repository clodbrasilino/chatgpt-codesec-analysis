#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* key;
    int value;
} Dictionary;

char** getDictionaryKeys(Dictionary* dictionary, int size) {
    char** keys = (char**) malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        keys[i] = dictionary[i].key;
    }
    return keys;
}

int main() {
    Dictionary dictionary[3];
    
    dictionary[0].key = "apple";
    dictionary[0].value = 10;
    
    dictionary[1].key = "banana";
    dictionary[1].value = 5;
    
    dictionary[2].key = "orange";
    dictionary[2].value = 7;
    
    int size = sizeof(dictionary) / sizeof(dictionary[0]);
    char** keys = getDictionaryKeys(dictionary, size);
    
    for (int i = 0; i < size; i++) {
        printf("%s\n", keys[i]);
        free(keys[i]);
    }
    
    free(keys);
    
    return 0;
}