#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

void dictionary_init(Dictionary *dict, size_t initial_capacity) {
    dict->size = 0;
    dict->capacity = initial_capacity;
    dict->entries = (DictionaryEntry *)malloc(initial_capacity * sizeof(DictionaryEntry));
}

void dictionary_deinit(Dictionary *dict) {
    for (size_t i = 0; i < dict->size; ++i) {
        free(dict->entries[i].key);
    }
    free(dict->entries);
}

int dictionary_contains(const Dictionary *dict, const char *key) {
    for (size_t i = 0; i < dict->size; ++i) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            return 1;
        }
    }
    return 0;
}

void dictionary_add(Dictionary *dict, const char *key, int value) {
    if (dict->size >= dict->capacity) {
        dict->capacity *= 2;
        dict->entries = (DictionaryEntry *)realloc(dict->entries, dict->capacity * sizeof(DictionaryEntry));
    }

    dict->entries[dict->size].key = strdup(key);
    dict->entries[dict->size].value = value;
    ++dict->size;
}

void merge_dictionaries(Dictionary *dest, const Dictionary *src) {
    for (size_t i = 0; i < src->size; ++i) {
        if (!dictionary_contains(dest, src->entries[i].key)) {
            dictionary_add(dest, src->entries[i].key, src->entries[i].value);
        }
    }
}

int main() {
    Dictionary dict1, dict2;

    dictionary_init(&dict1, 2);
    dictionary_init(&dict2, 2);

    dictionary_add(&dict1, "apple", 10);
    dictionary_add(&dict1, "banana", 20);

    dictionary_add(&dict2, "orange", 30);
    dictionary_add(&dict2, "banana", 25);

    merge_dictionaries(&dict1, &dict2);

    for (size_t i = 0; i < dict1.size; ++i) {
        printf("%s: %d\n", dict1.entries[i].key, dict1.entries[i].value);
    }

    dictionary_deinit(&dict1);
    dictionary_deinit(&dict2);

    return 0;
}