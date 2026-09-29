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
    size_t capacity;
} Dictionary;

Dictionary* create_dictionary(size_t capacity) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }
    dict->items = (KeyValuePair *)malloc(capacity * sizeof(KeyValuePair));
    if (!dict->items) {
        free(dict);
        return NULL;
    }
    dict->count = 0;
    dict->capacity = capacity;
    return dict;
}

void destroy_dictionary(Dictionary *dict) {
    if (dict) {
        if (dict->items) {
            for (size_t i = 0; i < dict->count; i++) {
                free(dict->items[i].key);
            }
            free(dict->items);
        }
        free(dict);
    }
}

int add_item(Dictionary *dict, const char *key, int value) {
    if (!dict || !key || dict->count >= dict->capacity) {
        return 0;
    }
    char *key_copy = strdup(key);
    if (!key_copy) {
        return 0;
    }
    dict->items[dict->count].key = key_copy;
    dict->items[dict->count].value = value;
    dict->count++;
    return 1;
}

int get_element_by_index(const Dictionary *dict, size_t index, KeyValuePair *out_pair) {
    if (!dict || !out_pair || index >= dict->count) {
        return 0;
    }
    out_pair->key = dict->items[index].key;
    out_pair->value = dict->items[index].value;
    return 1;
}

int main(void) {
    Dictionary *dict = create_dictionary(10);
    if (!dict) {
        return EXIT_FAILURE;
    }

    if (!add_item(dict, "apple", 10)) {
        destroy_dictionary(dict);
        return EXIT_FAILURE;
    }
    if (!add_item(dict, "banana", 20)) {
        destroy_dictionary(dict);
        return EXIT_FAILURE;
    }
    if (!add_item(dict, "cherry", 30)) {
        destroy_dictionary(dict);
        return EXIT_FAILURE;
    }

    KeyValuePair pair;
    size_t index = 1;

    if (get_element_by_index(dict, index, &pair)) {
        printf("Index %zu -> Key: %s, Value: %d\n", index, pair.key, pair.value);
    } else {
        printf("Index %zu out of bounds or invalid arguments.\n", index);
    }

    destroy_dictionary(dict);
    return EXIT_SUCCESS;
}