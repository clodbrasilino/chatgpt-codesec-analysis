#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} DictEntry;

typedef struct {
    int size;
    DictEntry *entries;
} Dictionary;

Dictionary* createDictionary() {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->size = 0;
    dict->entries = NULL;
    return dict;
}

void freeDictionary(Dictionary *dict) {
    if (dict) {
        for (int i = 0; i < dict->size; ++i) {
            free(dict->entries[i].key);
        }
        free(dict->entries);
        free(dict);
    }
}

int findKey(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->size; ++i) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

void addOrUpdateEntry(Dictionary *dict, const char *key, int value) {
    int index = findKey(dict, key);
    if (index != -1) {
        dict->entries[index].value = value;
    } else {
        dict->entries = (DictEntry*)realloc(dict->entries, (dict->size + 1) * sizeof(DictEntry));
        if (!dict->entries) return;
        dict->entries[dict->size].key = strdup(key);
        dict->entries[dict->size].value = value;
        dict->size++;
    }
}

Dictionary* mergeDictionaries(Dictionary *dict1, Dictionary *dict2) {
    Dictionary *mergedDict = createDictionary();
    if (!mergedDict) return NULL;
    
    for (int i = 0; i < dict1->size; ++i) {
        addOrUpdateEntry(mergedDict, dict1->entries[i].key, dict1->entries[i].value);
    }
    for (int i = 0; i < dict2->size; ++i) {
        addOrUpdateEntry(mergedDict, dict2->entries[i].key, dict2->entries[i].value);
    }
    
    return mergedDict;
}

void printDictionary(Dictionary *dict) {
    for (int i = 0; i < dict->size; ++i) {
        printf("%s: %d\n", dict->entries[i].key, dict->entries[i].value);
    }
}

int main() {
    Dictionary *dict1 = createDictionary();
    addOrUpdateEntry(dict1, "one", 1);
    addOrUpdateEntry(dict1, "two", 2);

    Dictionary *dict2 = createDictionary();
    addOrUpdateEntry(dict2, "two", 20);
    addOrUpdateEntry(dict2, "three", 3);

    Dictionary *mergedDict = mergeDictionaries(dict1, dict2);
    printDictionary(mergedDict);

    freeDictionary(dict1);
    freeDictionary(dict2);
    freeDictionary(mergedDict);

    return 0;
}