#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
} Dictionary;

int are_all_values_same(const Dictionary *dict) {
    if (dict == NULL || dict->entries == NULL) {
        return 0;
    }
    
    if (dict->size <= 1) {
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
    Dictionary dict1;
    dict1.size = 3;
    dict1.entries = (Entry *)malloc(dict1.size * sizeof(Entry));
    if (dict1.entries == NULL) {
        return EXIT_FAILURE;
    }
    dict1.entries[0].key = 1; dict1.entries[0].value = 42;
    dict1.entries[1].key = 2; dict1.entries[1].value = 42;
    dict1.entries[2].key = 3; dict1.entries[2].value = 42;

    Dictionary dict2;
    dict2.size = 3;
    dict2.entries = (Entry *)malloc(dict2.size * sizeof(Entry));
    if (dict2.entries == NULL) {
        free(dict1.entries);
        return EXIT_FAILURE;
    }
    dict2.entries[0].key = 1; dict2.entries[0].value = 10;
    dict2.entries[1].key = 2; dict2.entries[1].value = 20;
    dict2.entries[2].key = 3; dict2.entries[2].value = 30;

    Dictionary dict3;
    dict3.size = 0;
    dict3.entries = NULL;

    printf("Dict1 all same: %d\n", are_all_values_same(&dict1));
    printf("Dict2 all same: %d\n", are_all_values_same(&dict2));
    printf("Dict3 all same: %d\n", are_all_values_same(&dict3));

    free(dict1.entries);
    free(dict2.entries);

    return EXIT_SUCCESS;
}