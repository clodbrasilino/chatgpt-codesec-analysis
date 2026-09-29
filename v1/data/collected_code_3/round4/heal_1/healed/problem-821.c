#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} Item;

typedef struct {
    Item *items;
    int size;
    int capacity;
} Dictionary;

Dictionary* createDictionary() {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->items = malloc(sizeof(Item) * 10);
    if (dict->items == NULL) {
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = 10;
    return dict;
}

void add(Dictionary *dict, char *key, char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return;
    }
    if (dict->size == dict->capacity) {
        dict->capacity *= 2;
        Item *temp = realloc(dict->items, sizeof(Item) * dict->capacity);
        if (temp == NULL) {
            return;
        }
        dict->items = temp;
    }
    dict->items[dict->size].key = strdup(key);
    dict->items[dict->size].value = strdup(value);
    dict->size++;
}

Dictionary* merge(Dictionary *dict1, Dictionary *dict2) {
    if (dict1 == NULL || dict2 == NULL) {
        return NULL;
    }
    Dictionary *result = createDictionary();
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < dict1->size; i++) {
        add(result, dict1->items[i].key, dict1->items[i].value);
    }
    for (int i = 0; i < dict2->size; i++) {
        add(result, dict2->items[i].key, dict2->items[i].value);
    }
    return result;
}

void printDictionary(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    for (int i = 0; i < dict->size; i++) {
        printf("%s: %s\n", dict->items[i].key, dict->items[i].value);
    }
}

int main() {
    Dictionary *dict1 = createDictionary();
    add(dict1, "key1", "value1");
    add(dict1, "key2", "value2");

    Dictionary *dict2 = createDictionary();
    add(dict2, "key3", "value3");
    add(dict2, "key4", "value4");

    Dictionary *merged = merge(dict1, dict2);
    printDictionary(merged);

    return 0;
}