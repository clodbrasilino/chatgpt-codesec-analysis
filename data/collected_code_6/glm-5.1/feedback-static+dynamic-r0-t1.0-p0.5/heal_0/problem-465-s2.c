#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictItem;

typedef struct {
    DictItem *items;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary* dict_create(size_t capacity) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->items = malloc(capacity * sizeof(DictItem));
    if (!dict->items) {
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

int dict_insert(Dictionary *dict, const char *key, const char *value) {
    if (!dict || !key) return -1;
    if (dict->size >= dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        DictItem *new_items = realloc(dict->items, new_capacity * sizeof(DictItem));
        if (!new_items) return -1;
        dict->items = new_items;
        dict->capacity = new_capacity;
    }
    dict->items[dict->size].key = strdup(key);
    if (!dict->items[dict->size].key) return -1;
    if (value) {
        dict->items[dict->size].value = strdup(value);
        if (!dict->items[dict->size].value) {
            free(dict->items[dict->size].key);
            return -1;
        }
    } else {
        dict->items[dict->size].value = NULL;
    }
    dict->size++;
    return 0;
}

Dictionary* dict_drop_empty(Dictionary *dict) {
    if (!dict) return NULL;
    size_t valid_count = 0;
    for (size_t i = 0; i < dict->size; i++) {
        if (dict->items[i].value != NULL && dict->items[i].value[0] != '\0') {
            if (valid_count != i) {
                dict->items[valid_count] = dict->items[i];
            }
            valid_count++;
        } else {
            free(dict->items[i].key);
            free(dict->items[i].value);
        }
    }
    dict->size = valid_count;
    return dict;
}

void dict_free(Dictionary *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->items[i].key);
        free(dict->items[i].value);
    }
    free(dict->items);
    free(dict);
}

int main(void) {
    Dictionary *dict = dict_create(4);
    if (!dict) return EXIT_FAILURE;

    dict_insert(dict, "a", "1");
    dict_insert(dict, "b", "");
    dict_insert(dict, "c", NULL);
    dict_insert(dict, "d", "4");

    dict = dict_drop_empty(dict);
    if (!dict) return EXIT_FAILURE;

    for (size_t i = 0; i < dict->size; i++) {
        printf("%s: %s\n", dict->items[i].key, dict->items[i].value);
    }

    dict_free(dict);
    return EXIT_SUCCESS;
}