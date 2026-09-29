#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

Dictionary *dict_create(size_t capacity)
{
    if (capacity == 0) {
        return NULL;
    }
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->entries = calloc(capacity, sizeof(DictEntry));
    if (dict->entries == NULL) {
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

int dict_add(Dictionary *dict, const char *key, const char *value)
{
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    if (dict->size >= dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        DictEntry *new_entries = realloc(dict->entries, new_capacity * sizeof(DictEntry));
        if (new_entries == NULL) {
            return -1;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }
    char *key_copy = malloc(strlen(key) + 1);
    if (key_copy == NULL) {
        return -1;
    }
    char *value_copy = malloc(strlen(value) + 1);
    if (value_copy == NULL) {
        free(key_copy);
        return -1;
    }
    strcpy(key_copy, key);
    strcpy(value_copy, value);
    dict->entries[dict->size].key = key_copy;
    dict->entries[dict->size].value = value_copy;
    dict->size++;
    return 0;
}

const DictEntry *dict_get_entry_by_index(const Dictionary *dict, size_t index)
{
    if (dict == NULL || index >= dict->size) {
        return NULL;
    }
    return &dict->entries[index];
}

const char *dict_get_key_by_index(const Dictionary *dict, size_t index)
{
    if (dict == NULL || index >= dict->size) {
        return NULL;
    }
    return dict->entries[index].key;
}

const char *dict_get_value_by_index(const Dictionary *dict, size_t index)
{
    if (dict == NULL || index >= dict->size) {
        return NULL;
    }
    return dict->entries[index].value;
}

void dict_free(Dictionary *dict)
{
    if (dict == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
        free(dict->entries[i].value);
    }
    free(dict->entries);
    free(dict);
}

int main(void)
{
    Dictionary *dict = dict_create(4);
    if (dict == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if (dict_add(dict, "name", "Alice") != 0 ||
        dict_add(dict, "city", "Paris") != 0 ||
        dict_add(dict, "language", "C") != 0) {
        fprintf(stderr, "Failed to add entry\n");
        dict_free(dict);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < dict->size; i++) {
        const char *key = dict_get_key_by_index(dict, i);
        const char *value = dict_get_value_by_index(dict, i);
        if (key != NULL && value != NULL) {
            printf("[%zu] %s: %s\n", i, key, value);
        }
    }

    size_t index = 1;
    const DictEntry *entry = dict_get_entry_by_index(dict, index);
    if (entry != NULL) {
        printf("Element at index %zu -> key: %s, value: %s\n",
               index, entry->key, entry->value);
    } else {
        printf("Index %zu is out of range\n", index);
    }

    dict_free(dict);
    return EXIT_SUCCESS;
}