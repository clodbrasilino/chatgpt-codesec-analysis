#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_KEY_LENGTH 64
#define MAX_DICT_SIZE 100

typedef struct {
    char key[MAX_KEY_LENGTH];
    int value;
} DictEntry;

typedef struct {
    DictEntry entries[MAX_DICT_SIZE];
    int size;
} Dictionary;

bool all_values_same(const Dictionary *dict) {
    if (dict == NULL || dict->size <= 1) {
        return true;
    }
    
    int first_value = dict->entries[0].value;
    for (int i = 1; i < dict->size; i++) {
        if (dict->entries[i].value != first_value) {
            return false;
        }
    }
    return true;
}

int main(void) {
    Dictionary dict;
    dict.size = 0;
    
    strcpy(dict.entries[dict.size].key, "a");
    dict.entries[dict.size].value = 5;
    dict.size++;
    
    strcpy(dict.entries[dict.size].key, "b");
    dict.entries[dict.size].value = 5;
    dict.size++;
    
    strcpy(dict.entries[dict.size].key, "c");
    dict.entries[dict.size].value = 5;
    dict.size++;
    
    if (all_values_same(&dict)) {
        printf("All values are the same\n");
    } else {
        printf("Values are different\n");
    }
    
    dict.entries[2].value = 10;
    
    if (all_values_same(&dict)) {
        printf("All values are the same\n");
    } else {
        printf("Values are different\n");
    }
    
    return 0;
}