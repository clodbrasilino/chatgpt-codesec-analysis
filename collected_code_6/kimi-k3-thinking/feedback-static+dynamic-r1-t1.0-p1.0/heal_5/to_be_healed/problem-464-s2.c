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
} Dictionary;

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t len = 0;

    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

Dictionary *dict_create(size_t capacity)
{
    Dictionary *dict;

    if (capacity == 0 || capacity > SIZE_MAX / sizeof(DictEntry)) {
        return NULL;
    }

    dict = malloc(sizeof(*dict));
    if (dict == NULL) {
        return NULL;
    }

    dict->entries = calloc(capacity, sizeof(*dict->entries));
    if (dict->entries == NULL) {
        free(dict);
        return NULL;
    }

    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

bool dict_add(Dictionary *dict, const char *key, int value)
{
    size_t key_len;
    char *key_copy;

    if (dict == NULL || key == NULL) {
        return false;
    }
    if (dict->size >= dict->capacity) {
        return false;
    }

    key_len = bounded_strlen(key, MAX_KEY_LEN);
    if (key_len >= MAX_KEY_LEN) {
        return false;
    }

    key_copy = malloc(key_len + 1);
    if (key_copy == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(key_copy, key, key_len);
    key_copy[key_len] = '\0';

    dict->entries[dict->size].key = key_copy;
    dict->entries[dict->size].value = value;
    dict->size++;
    return true;
}

bool dict_all_values_same(const Dictionary *dict, bool *result)
{
    int first_value;
    size_t i;

    if (dict == NULL || result == NULL || dict->size == 0) {
        return false;
    }

    *result = true;
    first_value = dict->entries[0].value;

    for (i = 1; i < dict->size; i++) {
        if (dict->entries[i].value != first_value) {
            *result = false;
            break;
        }
    }

    return true;
}

void dict_destroy(Dictionary *dict)
{
    if (dict != NULL) {
        if (dict->entries != NULL) {
            for (size_t i = 0; i < dict->size; i++) {
                free(dict->entries[i].key);
            }
            free(dict->entries);
        }
        free(dict);
    }
}

int main(void)
{
    Dictionary *dict;
    bool all_same = false;

    dict = dict_create(4);
    if (dict == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if (!dict_add(dict, "a", 5) ||
        !dict_add(dict, "b", 5) ||
        !dict_add(dict, "c", 5)) {
        fprintf(stderr, "Failed to add entries\n");
        dict_destroy(dict);
        return EXIT_FAILURE;
    }

    if (dict_all_values_same(dict, &all_same)) {
        printf("All values same: %s\n", all_same ? "true" : "false");
    } else {
        printf("Dictionary is empty or invalid\n");
    }

    dict_destroy(dict);
    dict = NULL;

    dict = dict_create(4);
    if (dict == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if (!dict_add(dict, "x", 10) ||
        !dict_add(dict, "y", 20)) {
        fprintf(stderr, "Failed to add entries\n");
        dict_destroy(dict);
        return EXIT_FAILURE;
    }

    if (dict_all_values_same(dict, &all_same)) {
        printf("All values same: %s\n", all_same ? "true" : "false");
    } else {
        printf("Dictionary is empty or invalid\n");
    }

    dict_destroy(dict);
    dict = NULL;

    return EXIT_SUCCESS;
}