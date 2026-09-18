#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    const char *key;
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair *items;
    size_t count;
} Dictionary;

bool are_all_values_same(const Dictionary *dict) {
    if (dict == NULL) {
        return false;
    }
    if (dict->count <= 1) {
        return true;
    }
    if (dict->items == NULL) {
        return false;
    }

    int first_value = dict->items[0].value;
    for (size_t i = 1; i < dict->count; ++i) {
        if (dict->items[i].value != first_value) {
            return false;
        }
    }

    return true;
}

int main(void) {
    Dictionary dict;
    dict.count = 3;
    dict.items = (KeyValuePair *)malloc(dict.count * sizeof(KeyValuePair));
    
    if (dict.items == NULL) {
        return EXIT_FAILURE;
    }

    dict.items[0].key = "apple";
    dict.items[0].value = 42;
    dict.items[1].key = "banana";
    dict.items[1].value = 42;
    dict.items[2].key = "cherry";
    dict.items[2].value = 42;

    if (are_all_values_same(&dict)) {
        printf("All values are the same.\n");
    } else {
        printf("Values are not the same.\n");
    }

    dict.items[2].value = 99;

    if (are_all_values_same(&dict)) {
        printf("All values are the same.\n");
    } else {
        printf("Values are not the same.\n");
    }

    free(dict.items);
    dict.items = NULL;
    dict.count = 0;

    return EXIT_SUCCESS;
}