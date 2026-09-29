#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair *items;
    size_t count;
} Dictionary;

Dictionary* create_dictionary_from_tuple(const char **tuple_keys, const int *tuple_values, size_t tuple_size) {
    if (!tuple_keys || !tuple_values || tuple_size == 0) {
        return NULL;
    }

    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }

    dict->items = (KeyValuePair *)malloc(tuple_size * sizeof(KeyValuePair));
    if (!dict->items) {
        free(dict);
        return NULL;
    }

    dict->count = 0;

    for (size_t i = 0; i < tuple_size; ++i) {
        if (!tuple_keys[i]) {
            for (size_t j = 0; j < dict->count; ++j) {
                free(dict->items[j].key);
            }
            free(dict->items);
            free(dict);
            return NULL;
        }

        dict->items[i].key = strdup(tuple_keys[i]);
        if (!dict->items[i].key) {
            for (size_t j = 0; j < dict->count; ++j) {
                free(dict->items[j].key);
            }
            free(dict->items);
            free(dict);
            return NULL;
        }
        dict->items[i].value = tuple_values[i];
        dict->count++;
    }

    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (dict) {
        for (size_t i = 0; i < dict->count; ++i) {
            free(dict->items[i].key);
        }
        free(dict->items);
        free(dict);
    }
}

int main() {
    const char *keys[] = {"apple", "banana", "cherry"};
    const int values[] = {10, 20, 30};
    size_t tuple_size = sizeof(keys) / sizeof(keys[0]);

    Dictionary *dict = create_dictionary_from_tuple(keys, values, tuple_size);

    if (dict) {
        for (size_t i = 0; i < dict->count; ++i) {
            printf("%s: %d\n", dict->items[i].key, dict->items[i].value);
        }
        free_dictionary(dict);
    } else {
        printf("Failed to create dictionary.\n");
    }

    return 0;
}