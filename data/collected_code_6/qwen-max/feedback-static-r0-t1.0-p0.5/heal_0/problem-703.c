#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    int size;
    int capacity;
} Dictionary;

Dictionary* createDictionary(int capacity) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->capacity = capacity;
    dict->size = 0;
    dict->entries = (DictionaryEntry*)calloc(capacity, sizeof(DictionaryEntry));
    return dict;
}

void freeDictionary(Dictionary *dict) {
    for (int i = 0; i < dict->size; ++i) {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }
    free(dict->entries);
    free(dict);
}

int findKeyIndex(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->size; ++i) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

int isKeyPresent(Dictionary *dict, const char *key) {
    return findKeyIndex(dict, key) != -1;
}

int main() {
    Dictionary *dict = createDictionary(5);

    dict->entries[0].key = strdup("apple");
    dict->entries[0].value = strdup("fruit");
    dict->size++;

    dict->entries[1].key = strdup("carrot");
    dict->entries[1].value = strdup("vegetable");
    dict->size++;

    const char *keyToFind = "apple";
    if (isKeyPresent(dict, keyToFind)) {
        printf("Key '%s' is present in the dictionary.\n", keyToFind);
    } else {
        printf("Key '%s' is not present in the dictionary.\n", keyToFind);
    }

    keyToFind = "banana";
    if (isKeyPresent(dict, keyToFind)) {
        printf("Key '%s' is present in the dictionary.\n", keyToFind);
    } else {
        printf("Key '%s' is not present in the dictionary.\n", keyToFind);
    }

    freeDictionary(dict);
    return 0;
}