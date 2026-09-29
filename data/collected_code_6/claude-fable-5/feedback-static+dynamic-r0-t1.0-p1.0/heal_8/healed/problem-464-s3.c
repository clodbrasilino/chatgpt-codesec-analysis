#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_KEY_LEN 64

typedef struct {
    char *key;
    int value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dict;

Dict *dict_create(size_t capacity);
void dict_destroy(Dict *dict);
bool dict_add(Dict *dict, const char *key, int value);
bool all_values_same(const Dict *dict);

Dict *dict_create(size_t capacity)
{
    Dict *dict = NULL;

    if (capacity == 0 || capacity > SIZE_MAX / sizeof(DictEntry)) {
        return NULL;
    }

    dict = malloc(sizeof(Dict));
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

void dict_destroy(Dict *dict)
{
    if (dict == NULL) {
        return;
    }

    if (dict->entries != NULL) {
        for (size_t i = 0; i < dict->size; i++) {
            free(dict->entries[i].key);
            dict->entries[i].key = NULL;
        }
        free(dict->entries);
        dict->entries = NULL;
    }

    dict->size = 0;
    dict->capacity = 0;
    free(dict);
}

bool dict_add(Dict *dict, const char *key, int value)
{
    size_t key_len;
    size_t alloc_len;
    char *key_copy;

    if (dict == NULL || key == NULL || dict->entries == NULL) {
        return false;
    }

    if (dict->size >= dict->capacity) {
        return false;
    }

    key_len = strnlen(key, MAX_KEY_LEN);
    if (key_len == 0 || key_len >= MAX_KEY_LEN) {
        return false;
    }

    alloc_len = key_len + 1;
    if (alloc_len <= key_len) {
        return false;
    }

    key_copy = malloc(alloc_len);
    if (key_copy == NULL) {
        return false;
    }

    memcpy(key_copy, key, key_len);
    key_copy[key_len] = '\0';

    dict->entries[dict->size].key = key_copy;
    dict->entries[dict->size].value = value;
    dict->size++;
    return true;
}

bool all_values_same(const Dict *dict)
{
    int first_value;

    if (dict == NULL || dict->entries == NULL || dict->size == 0) {
        return true;
    }

    first_value = dict->entries[0].value;
    for (size_t i = 1; i < dict->size; i++) {
        if (dict->entries[i].value != first_value) {
            return false;
        }
    }
    return true;
}

int main(void)
{
    Dict *dict1 = NULL;
    Dict *dict2 = NULL;
    int status = EXIT_SUCCESS;

    dict1 = dict_create(10);
    if (dict1 == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    dict2 = dict_create(10);
    if (dict2 == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        dict_destroy(dict1);
        return EXIT_FAILURE;
    }

    if (!dict_add(dict1, "apple", 5) ||
        !dict_add(dict1, "banana", 5) ||
        !dict_add(dict1, "cherry", 5)) {
        fprintf(stderr, "Failed to add entries to dict1\n");
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (!dict_add(dict2, "apple", 5) ||
        !dict_add(dict2, "banana", 3) ||
        !dict_add(dict2, "cherry", 5)) {
        fprintf(stderr, "Failed to add entries to dict2\n");
        status = EXIT_FAILURE;
        goto cleanup;
    }

    printf("dict1 all values same: %s\n", all_values_same(dict1) ? "true" : "false");
    printf("dict2 all values same: %s\n", all_values_same(dict2) ? "true" : "false");

cleanup:
    dict_destroy(dict1);
    dict_destroy(dict2);
    return status;
}