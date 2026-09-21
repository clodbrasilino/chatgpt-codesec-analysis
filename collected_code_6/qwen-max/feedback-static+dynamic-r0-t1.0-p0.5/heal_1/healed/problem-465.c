#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictionaryItem;

typedef struct {
    DictionaryItem *items;
    int size;
    int capacity;
} Dictionary;

Dictionary* createDictionary(int capacity) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (dict == NULL) return NULL;
    dict->items = (DictionaryItem*)malloc(capacity * sizeof(DictionaryItem));
    if (dict->items == NULL) {
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

void freeDictionary(Dictionary *dict) {
    for (int i = 0; i < dict->size; ++i) {
        free(dict->items[i].key);
        free(dict->items[i].value);
    }
    free(dict->items);
    free(dict);
}

int addDictionaryItem(Dictionary *dict, const char *key, const char *value) {
    if (dict->size >= dict->capacity) return -1;
    dict->items[dict->size].key = strdup(key);
    dict->items[dict->size].value = strdup(value);
    dict->size++;
    return 0;
}

Dictionary* dropEmptyItems(Dictionary *dict) {
    Dictionary *newDict = createDictionary(dict->capacity);
    if (newDict == NULL) return NULL;
    for (int i = 0; i < dict->size; ++i) {
        if (dict->items[i].value != NULL && strlen(dict->items[i].value) > 0) {
            if (addDictionaryItem(newDict, dict->items[i].key, dict->items[i].value) != 0) {
                freeDictionary(newDict);
                return NULL;
            }
        }
    }
    return newDict;
}

int main() {
    Dictionary *dict = createDictionary(10);
    if (dict == NULL) return 1;

    addDictionaryItem(dict, "key1", "value1");
    addDictionaryItem(dict, "key2", "");
    addDictionaryItem(dict, "key3", "value3");
    addDictionaryItem(dict, "key4", "");

    Dictionary *newDict = dropEmptyItems(dict);
    if (newDict == NULL) {
        freeDictionary(dict);
        return 1;
    }

    for (int i = 0; i < newDict->size; ++i) {
        printf("%s: %s\n", newDict->items[i].key, newDict->items[i].value);
    }

    freeDictionary(dict);
    freeDictionary(newDict);
    return 0;
}