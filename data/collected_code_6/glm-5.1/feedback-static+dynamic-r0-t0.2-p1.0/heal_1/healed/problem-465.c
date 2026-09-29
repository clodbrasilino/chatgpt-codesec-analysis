#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *key;
    const char *value;
} DictItem;

typedef struct {
    DictItem *items;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary *dictionary_create(size_t initial_capacity) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->items = malloc(initial_capacity * sizeof(DictItem));
    if (!dict->items) {
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = initial_capacity;
    return dict;
}

void dictionary_free(Dictionary *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->size; i++) {
        free((void *)dict->items[i].key);
        free((void *)dict->items[i].value);
    }
    free(dict->items);
    free(dict);
}

int dictionary_insert(Dictionary *dict, const char *key, const char *value) {
    if (!dict || !key) return -1;
    if (dict->size >= dict->capacity) {
        size_t new_capacity = dict->capacity == 0 ? 4 : dict->capacity * 2;
        DictItem *new_items = realloc(dict->items, new_capacity * sizeof(DictItem));
        if (!new_items) return -1;
        dict->items = new_items;
        dict->capacity = new_capacity;
    }
    char *k_copy = strdup(key);
    if (!k_copy) return -1;
    char *v_copy = value ? strdup(value) : NULL;
    if (value && !v_copy) {
        free(k_copy);
        return -1;
    }
    dict->items[dict->size].key = k_copy;
    dict->items[dict->size].value = v_copy;
    dict->size++;
    return 0;
}

Dictionary *dictionary_drop_empty(Dictionary *dict) {
    if (!dict) return NULL;
    size_t write_idx = 0;
    for (size_t read_idx = 0; read_idx < dict->size; read_idx++) {
        const char *val = dict->items[read_idx].value;
        if (val != NULL && val[0] != '\0') {
            if (write_idx != read_idx) {
                dict->items[write_idx] = dict->items[read_idx];
                dict->items[read_idx].key = NULL;
                dict->items[read_idx].value = NULL;
            }
            write_idx++;
        } else {
            free((void *)dict->items[read_idx].key);
            free((void *)dict->items[read_idx].value);
            dict->items[read_idx].key = NULL;
            dict->items[read_idx].value = NULL;
        }
    }
    dict->size = write_idx;
    return dict;
}

int main(void) {
    Dictionary *dict = dictionary_create(8);
    if (!dict) return EXIT_FAILURE;

    dictionary_insert(dict, "key1", "value1");
    dictionary_insert(dict, "key2", "");
    dictionary_insert(dict, "key3", NULL);
    dictionary_insert(dict, "key4", "value4");
    dictionary_insert(dict, "key5", "");

    const Dictionary *filtered = dictionary_drop_empty(dict);
    if (!filtered) {
        dictionary_free(dict);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < dict->size; i++) {
        printf("Key: %s, Value: %s\n", dict->items[i].key, dict->items[i].value);
    }

    dictionary_free(dict);
    return EXIT_SUCCESS;
}