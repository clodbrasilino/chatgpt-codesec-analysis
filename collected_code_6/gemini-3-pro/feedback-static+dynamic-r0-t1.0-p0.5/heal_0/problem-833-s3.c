#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair *items;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary* create_dictionary(size_t capacity) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }
    dict->items = (KeyValuePair*)malloc(capacity * sizeof(KeyValuePair));
    if (!dict->items) {
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (dict) {
        for (size_t i = 0; i < dict->size; i++) {
            free(dict->items[i].key);
        }
        free(dict->items);
        free(dict);
    }
}

int add_to_dictionary(Dictionary *dict, const char *key, int value) {
    if (!dict || !key || dict->size >= dict->capacity) {
        return 0;
    }
    dict->items[dict->size].key = strdup(key);
    if (!dict->items[dict->size].key) {
        return 0;
    }
    dict->items[dict->size].value = value;
    dict->size++;
    return 1;
}

char** get_dictionary_keys(const Dictionary *dict, size_t *out_count) {
    if (!dict || !out_count) {
        return NULL;
    }

    char **keys = (char**)malloc(dict->size * sizeof(char*));
    if (!keys) {
        return NULL;
    }

    for (size_t i = 0; i < dict->size; i++) {
        keys[i] = strdup(dict->items[i].key);
        if (!keys[i]) {
            for (size_t j = 0; j < i; j++) {
                free(keys[j]);
            }
            free(keys);
            return NULL;
        }
    }

    *out_count = dict->size;
    return keys;
}

void free_keys_list(char **keys, size_t count) {
    if (keys) {
        for (size_t i = 0; i < count; i++) {
            free(keys[i]);
        }
        free(keys);
    }
}

int main(void) {
    Dictionary *dict = create_dictionary(10);
    if (!dict) {
        return 1;
    }

    if (!add_to_dictionary(dict, "apple", 1) ||
        !add_to_dictionary(dict, "banana", 2) ||
        !add_to_dictionary(dict, "cherry", 3)) {
        free_dictionary(dict);
        return 1;
    }

    size_t key_count = 0;
    char **keys = get_dictionary_keys(dict, &key_count);
    
    if (keys) {
        for (size_t i = 0; i < key_count; i++) {
            printf("%s\n", keys[i]);
        }
        free_keys_list(keys, key_count);
    }

    free_dictionary(dict);
    return 0;
}