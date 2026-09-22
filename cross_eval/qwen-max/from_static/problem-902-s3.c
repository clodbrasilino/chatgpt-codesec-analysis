#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

void dict_init(Dictionary *dict, size_t initial_capacity) {
    dict->size = 0;
    dict->capacity = initial_capacity;
    dict->entries = (DictEntry *)malloc(initial_capacity * sizeof(DictEntry));
}

void dict_add(Dictionary *dict, const char *key, int value) {
    if (dict->size >= dict->capacity) {
        dict->capacity *= 2;
        dict->entries = (DictEntry *)realloc(dict->entries, dict->capacity * sizeof(DictEntry));
    }
    DictEntry *entry = &dict->entries[dict->size++];
    entry->key = strdup(key);
    entry->value = value;
}

int dict_get(const Dictionary *dict, const char *key, int default_value) {
    for (size_t i = 0; i < dict->size; ++i) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            return dict->entries[i].value;
        }
    }
    return default_value;
}

Dictionary *combine_dictionaries(const Dictionary *dict1, const Dictionary *dict2) {
    Dictionary *result = (Dictionary *)malloc(sizeof(Dictionary));
    dict_init(result, dict1->size + dict2->size);

    for (size_t i = 0; i < dict1->size; ++i) {
        const char *key = dict1->entries[i].key;
        int val1 = dict1->entries[i].value;
        int val2 = dict_get(dict2, key, 0);
        dict_add(result, key, val1 + val2);
    }

    for (size_t i = 0; i < dict2->size; ++i) {
        const char *key = dict2->entries[i].key;
        if (dict_get(result, key, -1) == -1) {
            dict_add(result, key, dict2->entries[i].value);
        }
    }

    return result;
}

void dict_free(Dictionary *dict) {
    for (size_t i = 0; i < dict->size; ++i) {
        free(dict->entries[i].key);
    }
    free(dict->entries);
    free(dict);
}

int main() {
    Dictionary dict1, dict2;
    dict_init(&dict1, 4);
    dict_init(&dict2, 4);

    dict_add(&dict1, "apple", 2);
    dict_add(&dict1, "banana", 3);
    dict_add(&dict2, "apple", 5);
    dict_add(&dict2, "orange", 7);

    Dictionary *combined = combine_dictionaries(&dict1, &dict2);

    for (size_t i = 0; i < combined->size; ++i) {
        printf("%s: %d\n", combined->entries[i].key, combined->entries[i].value);
    }

    dict_free(&dict1);
    dict_free(&dict2);
    dict_free(combined);

    return 0;
}