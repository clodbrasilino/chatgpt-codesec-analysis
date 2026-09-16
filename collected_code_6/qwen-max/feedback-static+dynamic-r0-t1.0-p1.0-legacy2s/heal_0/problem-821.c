#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t count;
    size_t capacity;
} Dictionary;

void dictionary_init(Dictionary *dict, size_t initial_capacity) {
    dict->entries = (DictionaryEntry *)malloc(initial_capacity * sizeof(DictionaryEntry));
    if (dict->entries == NULL) exit(EXIT_FAILURE);
    dict->count = 0;
    dict->capacity = initial_capacity;
}

void dictionary_insert(Dictionary *dict, const char *key, int value) {
    if (dict->count >= dict->capacity) {
        dict->capacity *= 2;
        dict->entries = (DictionaryEntry *)realloc(dict->entries, dict->capacity * sizeof(DictionaryEntry));
        if (dict->entries == NULL) exit(EXIT_FAILURE);
    }
    dict->entries[dict->count].key = strdup(key);
    if (dict->entries[dict->count].key == NULL) exit(EXIT_FAILURE);
    dict->entries[dict->count].value = value;
    dict->count++;
}

void dictionary_merge(Dictionary *dest, const Dictionary *src) {
    for (size_t i = 0; i < src->count; i++) {
        dictionary_insert(dest, src->entries[i].key, src->entries[i].value);
    }
}

void dictionary_free(Dictionary *dict) {
    for (size_t i = 0; i < dict->count; i++) {
        free(dict->entries[i].key);
    }
    free(dict->entries);
    dict->count = 0;
    dict->capacity = 0;
}

int main() {
    Dictionary dict1, dict2, mergedDict;
    dictionary_init(&dict1, 2);
    dictionary_init(&dict2, 2);
    dictionary_init(&mergedDict, 4);

    dictionary_insert(&dict1, "one", 1);
    dictionary_insert(&dict1, "two", 2);
    dictionary_insert(&dict2, "three", 3);
    dictionary_insert(&dict2, "four", 4);

    dictionary_merge(&mergedDict, &dict1);
    dictionary_merge(&mergedDict, &dict2);

    for (size_t i = 0; i < mergedDict.count; i++) {
        printf("%s: %d\n", mergedDict.entries[i].key, mergedDict.entries[i].value);
    }

    dictionary_free(&dict1);
    dictionary_free(&dict2);
    dictionary_free(&mergedDict);

    return 0;
}