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

Dictionary *dictionary_create(size_t initial_capacity) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->entries = malloc(initial_capacity * sizeof(DictionaryEntry));
    if (!dict->entries) {
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = initial_capacity;
    return dict;
}

int dictionary_insert(Dictionary *dict, const char *key, int value) {
    if (!dict || !key) return -1;
    if (dict->size >= dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        DictionaryEntry *new_entries = realloc(dict->entries, new_capacity * sizeof(DictionaryEntry));
        if (!new_entries) return -1;
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }
    char *new_key = strdup(key);
    if (!new_key) return -1;
    dict->entries[dict->size].key = new_key;
    dict->entries[dict->size].value = value;
    dict->size++;
    return 0;
}

int dictionary_get_key_by_index(Dictionary *dict, size_t index, char **key) {
    if (!dict || !key) return -1;
    if (index >= dict->size) return -1;
    *key = dict->entries[index].key;
    return 0;
}

void dictionary_destroy(Dictionary *dict) {
    if (!dict) return;
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
    }
    free(dict->entries);
    free(dict);
}

int main(void) {
    Dictionary *dict = dictionary_create(4);
    if (!dict) {
        return EXIT_FAILURE;
    }

    dictionary_insert(dict, "apple", 1);
    dictionary_insert(dict, "banana", 2);
    dictionary_insert(dict, "cherry", 3);

    char *key = NULL;
    int result;

    result = dictionary_get_key_by_index(dict, 1, &key);
    if (result == 0) {
        printf("Key at index 1: %s\n", key);
    }

    result = dictionary_get_key_by_index(dict, 5, &key);
    if (result != 0) {
        printf("Index 5 is out of bounds.\n");
    }

    dictionary_destroy(dict);
    return EXIT_SUCCESS;
}