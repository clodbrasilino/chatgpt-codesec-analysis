#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictItem;

typedef struct {
    DictItem *items;
    size_t count;
    size_t capacity;
} Dictionary;

Dictionary* create_dictionary(size_t capacity) {
    if (capacity == 0) return NULL;
    
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (!dict) return NULL;

    dict->items = (DictItem*)malloc(capacity * sizeof(DictItem));
    if (!dict->items) {
        free(dict);
        return NULL;
    }

    dict->count = 0;
    dict->capacity = capacity;
    return dict;
}

int add_item(Dictionary *dict, const char *key, const char *value) {
    if (!dict || !key) return -1;
    if (dict->count >= dict->capacity) return -1;

    dict->items[dict->count].key = strdup(key);
    if (!dict->items[dict->count].key) return -1;

    if (value) {
        dict->items[dict->count].value = strdup(value);
        if (!dict->items[dict->count].value) {
            free(dict->items[dict->count].key);
            return -1;
        }
    } else {
        dict->items[dict->count].value = NULL;
    }

    dict->count++;
    return 0;
}

void drop_empty_items(Dictionary *dict) {
    if (!dict) return;

    size_t valid_count = 0;
    for (size_t i = 0; i < dict->count; i++) {
        if (dict->items[i].value != NULL && strlen(dict->items[i].value) > 0) {
            if (i != valid_count) {
                dict->items[valid_count] = dict->items[i];
            }
            valid_count++;
        } else {
            free(dict->items[i].key);
            free(dict->items[i].value);
            dict->items[i].key = NULL;
            dict->items[i].value = NULL;
        }
    }
    dict->count = valid_count;
}

void free_dictionary(Dictionary *dict) {
    if (!dict) return;
    
    for (size_t i = 0; i < dict->count; i++) {
        free(dict->items[i].key);
        free(dict->items[i].value);
    }
    free(dict->items);
    free(dict);
}

void print_dictionary(const Dictionary *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->count; i++) {
        printf("%s: %s\n", dict->items[i].key, dict->items[i].value ? dict->items[i].value : "NULL");
    }
}

int main() {
    Dictionary *dict = create_dictionary(5);
    if (!dict) return 1;

    add_item(dict, "key1", "value1");
    add_item(dict, "key2", "");
    add_item(dict, "key3", "value3");
    add_item(dict, "key4", NULL);
    add_item(dict, "key5", "value5");

    drop_empty_items(dict);
    print_dictionary(dict);
    free_dictionary(dict);

    return 0;
}