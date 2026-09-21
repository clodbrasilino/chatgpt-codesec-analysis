#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictionaryItem;

typedef struct {
    DictionaryItem **items;
    int size;
    int capacity;
} Dictionary;

Dictionary* create_dictionary(int capacity) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (dict == NULL) return NULL;
    dict->items = (DictionaryItem**)calloc(capacity, sizeof(DictionaryItem*));
    if (dict->items == NULL) {
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

void free_dictionary(Dictionary *dict) {
    if (dict == NULL) return;
    for (int i = 0; i < dict->size; ++i) {
        if (dict->items[i] != NULL) {
            free(dict->items[i]->key);
            free(dict->items[i]->value);
            free(dict->items[i]);
        }
    }
    free(dict->items);
    free(dict);
}

int add_item(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || dict->size >= dict->capacity) {
        return -1;
    }
    DictionaryItem *item = (DictionaryItem*)malloc(sizeof(DictionaryItem));
    if (item == NULL) return -1;
    item->key = strdup(key);
    if (item->key == NULL) {
        free(item);
        return -1;
    }
    item->value = strdup(value);
    if (item->value == NULL) {
        free(item->key);
        free(item);
        return -1;
    }
    dict->items[dict->size++] = item;
    return 0;
}

Dictionary* drop_empty_items(Dictionary *dict) {
    if (dict == NULL) return NULL;
    Dictionary *new_dict = create_dictionary(dict->capacity);
    if (new_dict == NULL) return NULL;
    for (int i = 0; i < dict->size; ++i) {
        if (dict->items[i] != NULL && dict->items[i]->value != NULL && *dict->items[i]->value != '\0') {
            if (add_item(new_dict, dict->items[i]->key, dict->items[i]->value) == -1) {
                free_dictionary(new_dict);
                return NULL;
            }
        }
    }
    return new_dict;
}

int main() {
    Dictionary *dict = create_dictionary(5);
    if (dict == NULL) return -1;
    if (add_item(dict, "key1", "value1") == -1) goto cleanup;
    if (add_item(dict, "key2", "") == -1) goto cleanup;
    if (add_item(dict, "key3", "value3") == -1) goto cleanup;
    if (add_item(dict, "key4", "") == -1) goto cleanup;

    Dictionary *filtered_dict = drop_empty_items(dict);
    if (filtered_dict == NULL) goto cleanup;

    for (int i = 0; i < filtered_dict->size; ++i) {
        printf("%s: %s\n", filtered_dict->items[i]->key, filtered_dict->items[i]->value);
    }

cleanup:
    free_dictionary(dict);
    free_dictionary(filtered_dict);
    return 0;
}