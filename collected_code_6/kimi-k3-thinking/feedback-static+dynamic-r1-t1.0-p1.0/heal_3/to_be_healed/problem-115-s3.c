#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t count;
    size_t capacity;
} Dictionary;

static bool dict_init(Dictionary *dict, size_t capacity)
{
    if (dict == NULL) {
        return false;
    }
    dict->entries = NULL;
    dict->count = 0;
    dict->capacity = 0;
    if (capacity == 0) {
        return true;
    }
    if (capacity > SIZE_MAX / sizeof(DictEntry)) {
        return false;
    }
    dict->entries = calloc(capacity, sizeof(DictEntry));
    if (dict->entries == NULL) {
        return false;
    }
    dict->capacity = capacity;
    return true;
}

static void dict_free(Dictionary *dict)
{
    if (dict == NULL) {
        return;
    }
    if (dict->entries != NULL) {
        for (size_t i = 0; i < dict->count; i++) {
            free(dict->entries[i].key);
            free(dict->entries[i].value);
        }
        free(dict->entries);
    }
    dict->entries = NULL;
    dict->count = 0;
    dict->capacity = 0;
}

static size_t safe_string_length(const char *s, size_t max_len)
{
    size_t len = 0;

    if (s == NULL) {
        return 0;
    }
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

static char *dup_string(const char *s)
{
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }
    len = safe_string_length(s, MAX_STRING_LENGTH);
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, s, len);
    copy[len] = '\0';
    return copy;
}

static bool dict_add(Dictionary *dict, const char *key, const char *value)
{
    char *key_copy;
    char *value_copy;

    if (dict == NULL || key == NULL || value == NULL) {
        return false;
    }
    if (dict->entries == NULL || dict->count >= dict->capacity) {
        return false;
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
    dict->entries[dict->count].key = key_copy;
    dict->entries[dict->count].value = value_copy;
    dict->count++;
    return true;
}

static bool dict_is_empty(const Dictionary *dict)
{
    if (dict == NULL) {
        return true;
    }
    return dict->count == 0;
}

bool all_dicts_empty(const Dictionary *dicts, size_t num_dicts)
{
    if (dicts == NULL && num_dicts > 0) {
        return false;
    }
    for (size_t i = 0; i < num_dicts; i++) {
        if (!dict_is_empty(&dicts[i])) {
            return false;
        }
    }
    return true;
}

int main(void)
{
    Dictionary dicts[3];
    const size_t num_dicts = 3;
    int status = EXIT_SUCCESS;

    for (size_t i = 0; i < num_dicts; i++) {
        if (!dict_init(&dicts[i], 10)) {
            fprintf(stderr, "Failed to initialize dictionary %zu\n", i);
            for (size_t j = 0; j < i; j++) {
                dict_free(&dicts[j]);
            }
            return EXIT_FAILURE;
        }
    }

    if (all_dicts_empty(dicts, num_dicts)) {
        printf("All dictionaries are empty\n");
    } else {
        printf("Not all dictionaries are empty\n");
    }

    if (!dict_add(&dicts[1], "name", "Alice")) {
        fprintf(stderr, "Failed to add entry\n");
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (all_dicts_empty(dicts, num_dicts)) {
        printf("All dictionaries are empty\n");
    } else {
        printf("Not all dictionaries are empty\n");
    }

cleanup:
    for (size_t i = 0; i < num_dicts; i++) {
        dict_free(&dicts[i]);
    }

    return status;
}