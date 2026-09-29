#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_KEY_LEN 64
#define MAX_VALUE_LEN 256

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
    }
    free(dict->entries);
    dict->entries = NULL;
    dict->count = 0;
    dict->capacity = 0;
}

static bool dict_add(Dictionary *dict, const char *key, const char *value)
{
    if (dict == NULL || key == NULL || value == NULL) {
        return false;
    }
    if (dict->entries == NULL || dict->count >= dict->capacity) {
        return false;
    }

    size_t key_len = strnlen(key, MAX_KEY_LEN);
    if (key_len >= MAX_KEY_LEN) {
        return false;
    }
    size_t value_len = strnlen(value, MAX_VALUE_LEN);
    if (value_len >= MAX_VALUE_LEN) {
        return false;
    }

    char *key_copy = malloc(key_len + 1);
    if (key_copy == NULL) {
        return false;
    }
    char *value_copy = malloc(value_len + 1);
    if (value_copy == NULL) {
        free(key_copy);
        return false;
    }

    int key_written = snprintf(key_copy, key_len + 1, "%s", key);
    if (key_written < 0 || (size_t)key_written >= key_len + 1) {
        free(key_copy);
        free(value_copy);
        return false;
    }

    int value_written = snprintf(value_copy, value_len + 1, "%s", value);
    if (value_written < 0 || (size_t)value_written >= value_len + 1) {
        free(key_copy);
        free(value_copy);
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