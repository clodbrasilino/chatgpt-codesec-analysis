#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *key;
    void *value;
} DictionaryItem;

typedef struct {
    DictionaryItem **items;
    int size;
} Dictionary;

Dictionary *create_dictionary(int size) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->items = (DictionaryItem **)calloc(size, sizeof(DictionaryItem *));
    if (!dict->items) { free(dict); return NULL; }
    dict->size = size;
    return dict;
}

void destroy_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->size; ++i) {
        if (dict->items[i]) {
            free(dict->items[i]->key);
            free(dict->items[i]->value);
            free(dict->items[i]);
        }
    }
    free(dict->items);
    free(dict);
}

void add_to_dictionary(Dictionary *dict, const char *key, void *value) {
    for (int i = 0; i < dict->size; ++i) {
        if (dict->items[i] == NULL) {
            DictionaryItem *item = (DictionaryItem *)malloc(sizeof(DictionaryItem));
            item->key = strdup(key);
            item->value = value;
            dict->items[i] = item;
            break;
        }
    }
}

void *get_value_by_index(Dictionary *dict, int index) {
    if (index < 0 || index >= dict->size) {
        return NULL;
    }
    return (dict->items[index]) ? dict->items[index]->value : NULL;
}

int main() {
    Dictionary *dict = create_dictionary(3);
    if (!dict) return 1;
    add_to_dictionary(dict, "key1", (void *)"value1");
    add_to_dictionary(dict, "key2", (void *)"value2");
    add_to_dictionary(dict, "key3", (void *)"value3");

    printf("Value at index 1: %s\n", (char *)get_value_by_index(dict, 1));

    destroy_dictionary(dict);
    return 0;
}