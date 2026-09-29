#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    int count;
    int capacity;
} Dictionary;

Dictionary* createDictionary(int capacity) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->capacity = capacity;
    dict->count = 0;
    dict->entries = (DictionaryEntry*)malloc(capacity * sizeof(DictionaryEntry));
    return dict;
}

void freeDictionary(Dictionary *dict) {
    for (int i = 0; i < dict->count; ++i) {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }
    free(dict->entries);
    free(dict);
}

int addEntry(Dictionary *dict, const char *key, const char *value) {
    if (dict->count >= dict->capacity) {
        return -1;
    }
    dict->entries[dict->count].key = strdup(key);
    dict->entries[dict->count].value = strdup(value);
    dict->count++;
    return 0;
}

Dictionary* mergeDictionaries(Dictionary *dict1, Dictionary *dict2) {
    Dictionary *mergedDict = createDictionary(dict1->count + dict2->count);
    for (int i = 0; i < dict1->count; ++i) {
        addEntry(mergedDict, dict1->entries[i].key, dict1->entries[i].value);
    }
    for (int i = 0; i < dict2->count; ++i) {
        addEntry(mergedDict, dict2->entries[i].key, dict2->entries[i].value);
    }
    return mergedDict;
}

int main() {
    Dictionary *dict1 = createDictionary(3);
    addEntry(dict1, "key1", "value1");
    addEntry(dict1, "key2", "value2");

    Dictionary *dict2 = createDictionary(3);
    addEntry(dict2, "key3", "value3");
    addEntry(dict2, "key4", "value4");

    Dictionary *mergedDict = mergeDictionaries(dict1, dict2);

    for (int i = 0; i < mergedDict->count; ++i) {
        printf("%s: %s\n", mergedDict->entries[i].key, mergedDict->entries[i].value);
    }

    freeDictionary(dict1);
    freeDictionary(dict2);
    freeDictionary(mergedDict);

    return 0;
}