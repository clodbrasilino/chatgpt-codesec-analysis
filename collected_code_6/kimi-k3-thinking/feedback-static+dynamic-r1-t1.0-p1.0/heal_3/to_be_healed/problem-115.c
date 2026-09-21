#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

typedef struct {
    char *key;
    char *value;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static size_t bounded_strlen(const char *src, size_t max_len)
{
    size_t len = 0;

    while (len < max_len && src[len] != '\0') {
        len++;
    }
    return len;
}

static char *dup_string(const char *src)
{
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }
    len = bounded_strlen(src, MAX_STRING_LENGTH + 1);
    if (len > MAX_STRING_LENGTH) {
        return NULL;
    }
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, src, len);
    copy[len] = '\0';
    return copy;
}

static bool dict_init(Dictionary *dict, size_t capacity)
{
    if (dict == NULL) {
        return false;
    }
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
    if (capacity > 0) {
        if (capacity > SIZE_MAX / sizeof(Entry)) {
            return false;
        }
        dict->entries = calloc(capacity, sizeof(Entry));
        if (dict->entries == NULL) {
            return false;
        }
        dict->capacity = capacity;
    }
    return true;
}

static bool dict_put(Dictionary *dict, const char *key, const char *value)
{
    char *key_copy;
    char *value_copy;

    if (dict == NULL || key == NULL || value == NULL) {
        return false;
    }
    if (dict->size == dict->capacity) {
        size_t new_capacity = (dict->capacity == 0) ? 4 : dict->capacity * 2;
        Entry *new_entries;

        if (new_capacity < dict->capacity ||
            new_capacity > SIZE_MAX / sizeof(Entry)) {
            return false;
        }
        new_entries = realloc(dict->entries, new_capacity * sizeof(Entry));
        if (new_entries == NULL) {
            return false;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }
    key_copy = dup_string(key);
    if (key_copy == NULL) {
        return false;
    }
    value_copy = dup_string(value);
    if (value_copy == NULL) {
        free(key_copy);
        return false;
    }
    dict->entries[dict->size].key = key_copy;
    dict->entries[dict->size].value = value_copy;
    dict->size++;
    return true;
}

static bool dict_is_empty(const Dictionary *dict)
{
    return dict == NULL || dict->size == 0;
}

static void dict_free(Dictionary *dict)
{
    if (dict != NULL) {
        size_t i;

        for (i = 0; i < dict->size; i++) {
            free(dict->entries[i].key);
            free(dict->entries[i].value);
        }
        free(dict->entries);
        dict->entries = NULL;
        dict->size = 0;
        dict->capacity = 0;
    }
}

bool all_dicts_empty(const Dictionary *dicts, size_t count)
{
    size_t i;

    if (dicts == NULL) {
        return true;
    }
    for (i = 0; i < count; i++) {
        if (!dict_is_empty(&dicts[i])) {
            return false;
        }
    }
    return true;
}

int main(void)
{
    Dictionary dicts[3];
    size_t i;
    bool result;

    for (i = 0; i < 3; i++) {
        if (!dict_init(&dicts[i], 0)) {
            size_t j;
            for (j = 0; j < i; j++) {
                dict_free(&dicts[j]);
            }
            fprintf(stderr, "Failed to initialize dictionary %zu\n", i);
            return EXIT_FAILURE;
        }
    }

    result = all_dicts_empty(dicts, 3);
    printf("All dictionaries empty: %s\n", result ? "true" : "false");

    if (!dict_put(&dicts[1], "name", "Alice")) {
        fprintf(stderr, "Failed to add entry\n");
        for (i = 0; i < 3; i++) {
            dict_free(&dicts[i]);
        }
        return EXIT_FAILURE;
    }

    result = all_dicts_empty(dicts, 3);
    printf("All dictionaries empty: %s\n", result ? "true" : "false");

    for (i = 0; i < 3; i++) {
        dict_free(&dicts[i]);
    }

    return EXIT_SUCCESS;
}