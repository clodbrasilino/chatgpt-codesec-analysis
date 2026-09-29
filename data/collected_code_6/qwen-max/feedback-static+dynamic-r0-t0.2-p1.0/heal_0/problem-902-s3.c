#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} DictEntry;

typedef struct {
    DictEntry **entries;
    int count;
} Dictionary;

Dictionary* createDictionary() {
    return (Dictionary*)calloc(1, sizeof(Dictionary));
}

void freeDictionary(Dictionary *dict) {
    for (int i = 0; i < dict->count; i++) {
        free(dict->entries[i]->key);
        free(dict->entries[i]);
    }
    free(dict->entries);
    free(dict);
}

DictEntry* findEntry(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->count; i++) {
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
        dict->entries = (DictEntry**)realloc(dict->entries, (dict->count + 1) * sizeof(DictEntry*));
        dict->entries[dict->count] = (DictEntry*)malloc(sizeof(DictEntry));
        dict->entries[dict->count]->key = strdup(key);
        dict->entries[dict->count]->value = value;
        dict->count++;
    }
}

Dictionary* combineDictionaries(Dictionary *dict1, Dictionary *dict2) {
    Dictionary *result = createDictionary();
    for (int i = 0; i < dict1->count; i++) {
        addOrUpdateEntry(result, dict1->entries[i]->key, dict1->entries[i]->value);
    }
    for (int i = 0; i < dict2->count; i++) {
        addOrUpdateEntry(result, dict2->entries[i]->key, dict2->entries[i]->value);
    }
    return result;
}

void printDictionary(Dictionary *dict) {
    for (int i = 0; i < dict->count; i++) {
        printf("%s: %d\n", dict->entries[i]->key, dict->entries[i]->value);
    }
}

int main() {
    Dictionary *dict1 = createDictionary();
    addOrUpdateEntry(dict1, "apple", 3);
    addOrUpdateEntry(dict1, "banana", 5);

    Dictionary *dict2 = createDictionary();
    addOrUpdateEntry(dict2, "apple", 2);
    addOrUpdateEntry(dict2, "orange", 4);

    Dictionary *combined = combineDictionaries(dict1, dict2);
    printDictionary(combined);

    freeDictionary(dict1);
    freeDictionary(dict2);
    freeDictionary(combined);

    return 0;
}