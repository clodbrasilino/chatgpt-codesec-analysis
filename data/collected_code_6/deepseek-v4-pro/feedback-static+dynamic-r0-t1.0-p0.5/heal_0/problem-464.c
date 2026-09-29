#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
} Dictionary;

int all_values_same(const Dictionary *dict) {
    if (dict == NULL || dict->size == 0) {
        return 1;
    }
    
    int first_value = dict->entries[0].value;
    for (size_t i = 1; i < dict->size; i++) {
        if (dict->entries[i].value != first_value) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    Dictionary dict;
    dict.size = 3;
    dict.entries = malloc(dict.size * sizeof(DictEntry));
    
    if (dict.entries == NULL) {
        return 1;
    }
    
    dict.entries[0].key = strdup("one");
    dict.entries[0].value = 10;
    dict.entries[1].key = strdup("two");
    dict.entries[1].value = 10;
    dict.entries[2].key = strdup("three");
    dict.entries[2].value = 10;
    
    if (all_values_same(&dict)) {
        printf("All values are same\n");
    } else {
        printf("Values are different\n");
    }
    
    for (size_t i = 0; i < dict.size; i++) {
        free(dict.entries[i].key);
    }
    free(dict.entries);
    
    return 0;
}