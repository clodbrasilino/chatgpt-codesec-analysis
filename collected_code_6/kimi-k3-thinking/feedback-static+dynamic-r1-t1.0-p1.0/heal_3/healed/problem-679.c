#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

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

static char *safe_string_copy(const char *str)
{
    if (str == NULL) {
        return NULL;
    }
    size_t length = strnlen(str, MAX_STRING_LENGTH);
    if (length == MAX_STRING_LENGTH) {
        return NULL;
    }
    if (length == SIZE_MAX) {
        return NULL;
    }
    char *copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < length; i++) {
        copy[i] = str[i];
    }
    copy[length] = '\0';
    return copy;
}

int dict_add(Dictionary *dict, const char *key, const char *value)
{
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    if (dict->size >= dict->capacity) {
        if (dict->capacity > SIZE_MAX / 2) {
            return -1;
        }
        size_t new_capacity = dict->capacity * 2;
        if (new_capacity > SIZE_MAX / sizeof(DictEntry)) {
            return -1;
        }
        DictEntry *new_entries = realloc(dict->entries, new_capacity * sizeof(DictEntry));
        if (new_entries == NULL) {
            return -1;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }
    char *key_copy = safe_string_copy(key);
    if (key_copy == NULL) {
        return -1;
    }
    char *value_copy = safe_string_copy(value);
    if (value_copy == NULL) {
        free(key_copy);
        return -1;
    }
    dict->entries[dict->size].key = key_copy;
    dict->entries[dict->size].value = value_copy;
    dict->size++;
    return 0;
}

const DictEntry *dict_get_entry_by_index(const Dictionary *dict, size_t index)
{
    if (dict == NULL || dict->entries == NULL || index >= dict->size) {
        return NULL;
    }
    return &dict->entries[index];
}

const char *dict_get_key_by_index(const Dictionary *dict, size_t index)
{
    if (dict == NULL || dict->entries == NULL || index >= dict->size) {
        return NULL;
    }
    return dict->entries[index].key;
}

const char *dict_get_value_by_index(const Dictionary *dict, size_t index)
{
    if (dict == NULL || dict->entries == NULL || index >= dict->size) {
        return NULL;
    }
    return dict->entries[index].value;
}

void dict_free(Dictionary *dict)
{
    if (dict == NULL) {
        return;
    }
    if (dict->entries != NULL) {
        for (size_t i = 0; i < dict->size; i++) {
            free(dict->entries[i].key);
            free(dict->entries[i].value);
        }
        free(dict->entries);
    }
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
    if (entry != NULL && entry->key != NULL && entry->value != NULL) {
        printf("Element at index %zu -> key: %s, value: %s\n",
               index, entry->key, entry->value);
    } else {
        printf("Index %zu is out of range\n", index);
    }

    dict_free(dict);
    return EXIT_SUCCESS;
}