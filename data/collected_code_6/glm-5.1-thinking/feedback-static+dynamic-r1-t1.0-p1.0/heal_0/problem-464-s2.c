#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *key;
    int value;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
} Dictionary;

int all_values_same(const Dictionary *dict) {
    if (dict == NULL) {
        return 0;
    }
    if (dict->size == 0) {
        return 1;
    }
    if (dict->entries == NULL) {
        return 0;
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
    dict1.entries = malloc(dict1.size * sizeof(Entry));
    if (dict1.entries == NULL) {
        return EXIT_FAILURE;
    }
    dict1.entries[0].key = "a";
    dict1.entries[0].value = 10;
    dict1.entries[1].key = "b";
    dict1.entries[1].value = 10;
    dict1.entries[2].key = "c";
    dict1.entries[2].value = 10;

    Dictionary dict2;
    dict2.size = 2;
    dict2.entries = malloc(dict2.size * sizeof(Entry));
    if (dict2.entries == NULL) {
        free(dict1.entries);
        return EXIT_FAILURE;
    }
    dict2.entries[0].key = "x";
    dict2.entries[0].value = 5;
    dict2.entries[1].key = "y";
    dict2.entries[1].value = 6;

    printf("%d\n", all_values_same(&dict1));
    printf("%d\n", all_values_same(&dict2));
    printf("%d\n", all_values_same(NULL));

    free(dict1.entries);
    free(dict2.entries);

    return EXIT_SUCCESS;
}