#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

void dictionary_init(Dictionary *dict, size_t capacity) {
    dict->entries = (DictionaryEntry *)malloc(capacity * sizeof(DictionaryEntry));
    if (dict->entries == NULL) {
        exit(EXIT_FAILURE);
    }
    dict->size = 0;
    dict->capacity = capacity;
}

void dictionary_add(Dictionary *dict, const char *key, const char *value) {
    if (dict->size >= dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        DictionaryEntry *new_entries = (DictionaryEntry *)realloc(dict->entries, new_capacity * sizeof(DictionaryEntry));
        if (new_entries == NULL) {
            exit(EXIT_FAILURE);
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }
    dict->entries[dict->size].key = strdup(key);
    if (dict->entries[dict->size].key == NULL) {
        exit(EXIT_FAILURE);
    }
    dict->entries[dict->size].value = strdup(value);
    if (dict->entries[dict->size].value == NULL) {
        free(dict->entries[dict->size].key);
        exit(EXIT_FAILURE);
    }
    dict->size++;
}

int compare_entries(const void *a, const void *b) {
    const DictionaryEntry *entry_a = (const DictionaryEntry *)a;
    const DictionaryEntry *entry_b = (const DictionaryEntry *)b;
    return strcmp(entry_a->key, entry_b->key);
}

void dictionary_sort(Dictionary *dict) {
    if (dict->size > 1) {
        qsort(dict->entries, dict->size, sizeof(DictionaryEntry), compare_entries);
    }
}

void dictionary_free(Dictionary *dict) {
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }
    free(dict->entries);
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
}

int main(void) {
    Dictionary dict;
    dictionary_init(&dict, 4);

    dictionary_add(&dict, "banana", "3");
    dictionary_add(&dict, "apple", "1");
    dictionary_add(&dict, "cherry", "2");
    dictionary_add(&dict, "date", "4");

    dictionary_sort(&dict);

    for (size_t i = 0; i < dict.size; i++) {
        printf("%s: %s\n", dict.entries[i].key, dict.entries[i].value);
    }

    dictionary_free(&dict);

    return 0;
}