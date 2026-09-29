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

Dictionary *dict_create(size_t initial_capacity) {
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

void dict_free(Dictionary *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->items[i].key);
        free(dict->items[i].value);
    }
    free(dict->items);
    free(dict);
}

int dict_insert(Dictionary *dict, const char *key, const char *value) {
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

Dictionary *dict_drop_empty(Dictionary *dict) {
    if (!dict) return NULL;
    size_t write_idx = 0;
    for (size_t read_idx = 0; read_idx < dict->size; read_idx++) {
        DictItem current = dict->items[read_idx];
        int is_empty = 0;
        if (!current.value) {
            is_empty = 1;
        } else if (current.value[0] == '\0') {
            is_empty = 1;
        }
        if (!is_empty) {
            if (write_idx != read_idx) {
                dict->items[write_idx] = current;
            }
            write_idx++;
        } else {
            free(current.key);
            free(current.value);
        }
    }
    dict->size = write_idx;
    if (dict->size < dict->capacity / 2 && dict->capacity > 4) {
        size_t new_capacity = dict->capacity / 2;
        DictItem *new_items = realloc(dict->items, new_capacity * sizeof(DictItem));
        if (new_items) {
            dict->items = new_items;
            dict->capacity = new_capacity;
        }
    }
    return dict;
}

int main(void) {
    Dictionary *dict = dict_create(8);
    if (!dict) return 1;

    dict_insert(dict, "key1", "value1");
    dict_insert(dict, "key2", "");
    dict_insert(dict, "key3", NULL);
    dict_insert(dict, "key4", "value4");
    dict_insert(dict, "key5", "");

    printf("Before drop_empty:\n");
    for (size_t i = 0; i < dict->size; i++) {
        printf("  %s: %s\n", dict->items[i].key, dict->items[i].value ? dict->items[i].value : "(null)");
    }

    Dictionary *result = dict_drop_empty(dict);
    if (!result) {
        dict_free(dict);
        return 1;
    }

    printf("\nAfter drop_empty:\n");
    for (size_t i = 0; i < dict->size; i++) {
        printf("  %s: %s\n", dict->items[i].key, dict->items[i].value ? dict->items[i].value : "(null)");
    }

    dict_free(dict);
    return 0;
}