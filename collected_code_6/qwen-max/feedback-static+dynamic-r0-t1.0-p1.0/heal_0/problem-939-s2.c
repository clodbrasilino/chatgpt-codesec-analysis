#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    int capacity;
    int size;
} Dictionary;

void dictionary_init(Dictionary *dict, int capacity) {
    dict->capacity = capacity;
    dict->size = 0;
    dict->entries = (DictionaryEntry *)malloc(capacity * sizeof(DictionaryEntry));
}

void dictionary_add(Dictionary *dict, const char *key, const char *value) {
    if (dict->size >= dict->capacity) {
        dict->capacity *= 2;
        dict->entries = (DictionaryEntry *)realloc(dict->entries, dict->capacity * sizeof(DictionaryEntry));
    }
    dict->entries[dict->size].key = strdup(key);
    dict->entries[dict->size].value = strdup(value);
    dict->size++;
}

int string_compare(const void *a, const void *b) {
    return strcmp(((DictionaryEntry *)a)->key, ((DictionaryEntry *)b)->key);
}

void sort_dictionary(Dictionary *dict) {
    qsort(dict->entries, dict->size, sizeof(DictionaryEntry), string_compare);
}

int main() {
    Dictionary dict;
    dictionary_init(&dict, 4);

    dictionary_add(&dict, "apple", "1");
    dictionary_add(&dict, "banana", "2");
    dictionary_add(&dict, "cherry", "3");
    dictionary_add(&dict, "date", "4");

    sort_dictionary(&dict);

    for (int i = 0; i < dict.size; i++) {
        printf("%s: %s\n", dict.entries[i].key, dict.entries[i].value);
        free(dict.entries[i].key);
        free(dict.entries[i].value);
    }

    free(dict.entries);
    return 0;
}