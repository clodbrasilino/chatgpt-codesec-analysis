#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *keys;
    int *values;
    int size;
} Dictionary;

Dictionary* create_empty_dictionary() {
    Dictionary *newDict = malloc(sizeof(Dictionary));
    if(newDict) {
        newDict->keys = NULL;
        newDict->values = NULL;
        newDict->size = 0;
    }
    return newDict;
}

Dictionary** create_dictionary_list(int count) {
    Dictionary **newList = malloc(sizeof(Dictionary*)*count);
    if(newList){
        for(int i=0; i<count; i++) {
            newList[i] = create_empty_dictionary();
            if(newList[i] == NULL) {
                for(int j=0; j<i; j++)
                    free(newList[j]);
                free(newList);
                return NULL;
            }
        }
    }
    return newList;
}

void free_dictionary(Dictionary *dict) {
    free(dict->keys);
    free(dict->values);
    free(dict);
}

void free_dictionary_list(Dictionary **dictList, int count) {
    for(int i=0; i<count; i++)
        free_dictionary(dictList[i]);
    free(dictList);
}

int main() {
    int count = 10;
    Dictionary **dictList = create_dictionary_list(count);
    if(dictList == NULL) {
        printf("Failed to allocate memory\n");
        return 1;
    }

    // Use the dictionary list here ...

    // Don't forget to free the memory
    free_dictionary_list(dictList, count);

    return 0;
}