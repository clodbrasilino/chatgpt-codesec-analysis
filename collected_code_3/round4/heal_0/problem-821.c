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
    dict->items = malloc(sizeof(Item) * 10);
    dict->size = 0;
    dict->capacity = 10;
    return dict;
}

void add(Dictionary *dict, char *key, char *value) {
    if (dict->size == dict->capacity) {
        dict->capacity *= 2;
        dict->items = realloc(dict->items, sizeof(Item) * dict->capacity);
    }
    dict->items[dict->size].key = strdup(key);
    dict->items[dict->size].value = strdup(value);
    dict->size++;
}

Dictionary* merge(Dictionary *dict1, Dictionary *dict2) {
    Dictionary *result = createDictionary();
    for (int i = 0; i < dict1->size; i++) {
        add(result, dict1->items[i].key, dict1->items[i].value);
    }
    for (int i = 0; i < dict2->size; i++) {
        add(result, dict2->items[i].key, dict2->items[i].value);
    }
    return result;
}

void printDictionary(Dictionary *dict) {
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