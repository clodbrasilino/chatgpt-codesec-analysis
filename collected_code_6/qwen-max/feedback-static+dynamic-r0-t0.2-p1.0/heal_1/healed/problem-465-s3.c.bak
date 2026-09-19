#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictionaryItem;

typedef struct {
    DictionaryItem *items;
    int count;
    int capacity;
} Dictionary;

Dictionary* create_dictionary(int initial_capacity) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->items = (DictionaryItem*)malloc(initial_capacity * sizeof(DictionaryItem));
    dict->count = 0;
    dict->capacity = initial_capacity;
    return dict;
}

void add_item(Dictionary *dict, const char *key, const char *value) {
    if (dict->count >= dict->capacity) {
        dict->capacity *= 2;
        dict->items = (DictionaryItem*)realloc(dict->items, dict->capacity * sizeof(DictionaryItem));
    }
    dict->items[dict->count].key = strdup(key);
    dict->items[dict->count].value = value ? strdup(value) : NULL;
    dict->count++;
}

void drop_empty_items(Dictionary *dict) {
    int write_index = 0;
    for (int i = 0; i < dict->count; i++) {
        if (dict->items[i].value != NULL && strlen(dict->items[i].value) > 0) {
            if (write_index != i) {
                dict->items[write_index] = dict->items[i];
            }
            write_index++;
        } else {
            free(dict->items[i].key);
            free(dict->items[i].value);
        }
    }
    dict->count = write_index;
}

void free_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->count; i++) {
        free(dict->items[i].key);
        free(dict->items[i].value);
    }
    free(dict->items);
    free(dict);
}

int main() {
    Dictionary *dict = create_dictionary(5);
    add_item(dict, "key1", "value1");
    add_item(dict, "key2", "");
    add_item(dict, "key3", "value3");
    add_item(dict, "key4", NULL);
    add_item(dict, "key5", "value5");

    drop_empty_items(dict);

    for (int i = 0; i < dict->count; i++) {
        printf("Key: %s, Value: %s\n", dict->items[i].key, dict->items[i].value);
    }

    free_dictionary(dict);
    return 0;
}