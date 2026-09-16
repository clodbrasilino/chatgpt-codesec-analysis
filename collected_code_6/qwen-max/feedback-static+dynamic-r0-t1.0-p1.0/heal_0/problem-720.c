#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *key;
    int value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t count;
} Dictionary;

Dictionary *createDictionary(size_t initialCapacity) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) return NULL;
    dict->entries = (DictEntry *)malloc(initialCapacity * sizeof(DictEntry));
    if (dict->entries == NULL) {
        free(dict);
        return NULL;
    }
    dict->count = 0;
    return dict;
}

void addEntry(Dictionary *dict, const char *key, int value) {
    if (dict == NULL || key == NULL) return;
    dict->entries[dict->count].key = strdup(key);
    dict->entries[dict->count].value = value;
    dict->count++;
}

typedef struct {
    Dictionary *first;
    Dictionary *second;
} Tuple;

Tuple *addDictToTuple(Tuple *tuple, Dictionary *newDict) {
    if (tuple == NULL) return NULL;
    Tuple *newTuple = (Tuple *)malloc(sizeof(Tuple));
    if (newTuple == NULL) return NULL;
    newTuple->first = tuple->first;
    newTuple->second = newDict;
    return newTuple;
}

int main() {
    Dictionary *dict1 = createDictionary(2);
    if (dict1 == NULL) return -1;
    addEntry(dict1, "apple", 5);

    Dictionary *dict2 = createDictionary(2);
    if (dict2 == NULL) {
        free(dict1->entries);
        free(dict1);
        return -1;
    }
    addEntry(dict2, "banana", 10);

    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        free(dict2->entries);
        free(dict2);
        free(dict1->entries);
        free(dict1);
        return -1;
    }
    tuple->first = dict1;
    tuple->second = NULL;

    Tuple *newTuple = addDictToTuple(tuple, dict2);
    if (newTuple == NULL) {
        free(dict2->entries);
        free(dict2);
        free(tuple);
        return -1;
    }

    // Clean up
    for (size_t i = 0; i < newTuple->first->count; ++i) {
        free(newTuple->first->entries[i].key);
    }
    free(newTuple->first->entries);
    free(newTuple->first);
    for (size_t i = 0; i < newTuple->second->count; ++i) {
        free(newTuple->second->entries[i].key);
    }
    free(newTuple->second->entries);
    free(newTuple->second);
    free(newTuple);

    return 0;
}