#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry **entries;
    int size;
    int capacity;
} Dictionary;

Dictionary* createDictionary(int initialCapacity) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->size = 0;
    dict->capacity = initialCapacity;
    dict->entries = (DictionaryEntry**)calloc(initialCapacity, sizeof(DictionaryEntry*));
    return dict;
}

void freeDictionary(Dictionary *dict) {
    for (int i = 0; i < dict->size; ++i) {
        free(dict->entries[i]->key);
        free(dict->entries[i]);
    }
    free(dict->entries);
    free(dict);
}

int findIndex(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->size; ++i) {
        if (strcmp(dict->entries[i]->key, key) == 0) {
            return i;
        }
    }
    return -1;
}

void addOrUpdateEntry(Dictionary *dict, const char *key, int value) {
    int index = findIndex(dict, key);
    if (index != -1) {
        dict->entries[index]->value = value;
    } else {
        if (dict->size >= dict->capacity) {
            dict->capacity *= 2;
            dict->entries = (DictionaryEntry**)realloc(dict->entries, dict->capacity * sizeof(DictionaryEntry*));
        }
        dict->entries[dict->size] = (DictionaryEntry*)malloc(sizeof(DictionaryEntry));
        dict->entries[dict->size]->key = strdup(key);
        dict->entries[dict->size]->value = value;
        dict->size++;
    }
}

Dictionary* mergeDictionaries(Dictionary *dict1, Dictionary *dict2) {
    Dictionary *mergedDict = createDictionary(dict1->size + dict2->size);
    for (int i = 0; i < dict1->size; ++i) {
        addOrUpdateEntry(mergedDict, dict1->entries[i]->key, dict1->entries[i]->value);
    }
    for (int i = 0; i < dict2->size; ++i) {
        addOrUpdateEntry(mergedDict, dict2->entries[i]->key, dict2->entries[i]->value);
    }
    return mergedDict;
}

int main() {
    Dictionary *dict1 = createDictionary(2);
    addOrUpdateEntry(dict1, "one", 1);
    addOrUpdateEntry(dict1, "two", 2);

    Dictionary *dict2 = createDictionary(2);
    addOrUpdateEntry(dict2, "two", 20);
    addOrUpdateEntry(dict2, "three", 3);

    Dictionary *mergedDict = mergeDictionaries(dict1, dict2);

    for (int i = 0; i < mergedDict->size; ++i) {
        printf("%s: %d\n", mergedDict->entries[i]->key, mergedDict->entries[i]->value);
    }

    freeDictionary(dict1);
    freeDictionary(dict2);
    freeDictionary(mergedDict);

    return 0;
}