#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} DictEntry;

typedef struct {
    DictEntry **entries;
    size_t count;
    size_t capacity;
} Dictionary;

Dictionary* createDictionary(size_t initialCapacity) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    dict->capacity = initialCapacity;
    dict->count = 0;
    dict->entries = (DictEntry **)calloc(initialCapacity, sizeof(DictEntry *));
    return dict;
}

void freeDictionary(Dictionary *dict) {
    for (size_t i = 0; i < dict->count; ++i) {
        free(dict->entries[i]->key);
        free(dict->entries[i]);
    }
    free(dict->entries);
    free(dict);
}

DictEntry* findEntry(Dictionary *dict, const char *key) {
    for (size_t i = 0; i < dict->count; ++i) {
        if (strcmp(dict->entries[i]->key, key) == 0) {
            return dict->entries[i];
        }
    }
    return NULL;
}

void addOrUpdateEntry(Dictionary *dict, const char *key, int value) {
    DictEntry *entry = findEntry(dict, key);
    if (entry) {
        entry->value += value;
    } else {
        if (dict->count >= dict->capacity) {
            dict->capacity *= 2;
            dict->entries = (DictEntry **)realloc(dict->entries, dict->capacity * sizeof(DictEntry *));
        }
        entry = (DictEntry *)malloc(sizeof(DictEntry));
        entry->key = strdup(key);
        entry->value = value;
        dict->entries[dict->count++] = entry;
    }
}

void combineDictionaries(Dictionary *dest, const Dictionary *src) {
    for (size_t i = 0; i < src->count; ++i) {
        addOrUpdateEntry(dest, src->entries[i]->key, src->entries[i]->value);
    }
}

int main() {
    Dictionary *dict1 = createDictionary(4);
    addOrUpdateEntry(dict1, "a", 1);
    addOrUpdateEntry(dict1, "b", 2);

    Dictionary *dict2 = createDictionary(4);
    addOrUpdateEntry(dict2, "b", 3);
    addOrUpdateEntry(dict2, "c", 4);

    combineDictionaries(dict1, dict2);

    for (size_t i = 0; i < dict1->count; ++i) {
        printf("%s: %d\n", dict1->entries[i]->key, dict1->entries[i]->value);
    }

    freeDictionary(dict1);
    freeDictionary(dict2);

    return 0;
}