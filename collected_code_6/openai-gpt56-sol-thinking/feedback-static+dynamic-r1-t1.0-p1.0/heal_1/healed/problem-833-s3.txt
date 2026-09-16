#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    DICTIONARY_OK = 0,
    DICTIONARY_INVALID_ARGUMENT,
    DICTIONARY_OUT_OF_MEMORY,
    DICTIONARY_OVERFLOW
} DictionaryStatus;

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t count;
    size_t capacity;
} Dictionary;

static int dictionary_is_valid(const Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return 0;
    }

    if (dictionary->count > dictionary->capacity) {
        return 0;
    }

    if ((dictionary->capacity == 0) != (dictionary->entries == NULL)) {
        return 0;
    }

    for (i = 0; i < dictionary->count; ++i) {
        if (dictionary->entries[i].key == NULL ||
            dictionary->entries[i].value == NULL) {
            return 0;
        }
    }

    return 1;
}

static char *duplicate_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    length = strlen(source);
    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length + 1);
    return copy;
}

static DictionaryStatus dictionary_reserve(
    Dictionary *dictionary,
    size_t minimum_capacity)
{
    size_t new_capacity;
    DictionaryEntry *new_entries;

    if (!dictionary_is_valid(dictionary)) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    if (minimum_capacity <= dictionary->capacity) {
        return DICTIONARY_OK;
    }

    new_capacity = dictionary->capacity == 0 ? 4 : dictionary->capacity;

    while (new_capacity < minimum_capacity) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = minimum_capacity;
            break;
        }

        new_capacity *= 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*new_entries)) {
        return DICTIONARY_OVERFLOW;
    }

    new_entries = realloc(
        dictionary->entries,
        new_capacity * sizeof(*new_entries));

    if (new_entries == NULL) {
        return DICTIONARY_OUT_OF_MEMORY;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = new_capacity;

    return DICTIONARY_OK;
}

static DictionaryStatus dictionary_put(
    Dictionary *dictionary,
    const char *key,
    const char *value)
{
    size_t i;
    char *key_copy;
    char *value_copy;
    DictionaryStatus status;

    if (!dictionary_is_valid(dictionary) || key == NULL || value == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    for (i = 0; i < dictionary->count; ++i) {
        if (strcmp(dictionary->entries[i].key, key) == 0) {
            value_copy = duplicate_string(value);
            if (value_copy == NULL) {
                return DICTIONARY_OUT_OF_MEMORY;
            }

            free(dictionary->entries[i].value);
            dictionary->entries[i].value = value_copy;

            return DICTIONARY_OK;
        }
    }

    if (dictionary->count == SIZE_MAX) {
        return DICTIONARY_OVERFLOW;
    }

    key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        return DICTIONARY_OUT_OF_MEMORY;
    }

    value_copy = duplicate_string(value);
    if (value_copy == NULL) {
        free(key_copy);
        return DICTIONARY_OUT_OF_MEMORY;
    }

    status = dictionary_reserve(dictionary, dictionary->count + 1);
    if (status != DICTIONARY_OK) {
        free(value_copy);
        free(key_copy);
        return status;
    }

    dictionary->entries[dictionary->count].key = key_copy;
    dictionary->entries[dictionary->count].value = value_copy;
    ++dictionary->count;

    return DICTIONARY_OK;
}

static DictionaryStatus dictionary_get_keys(
    const Dictionary *dictionary,
    char ***keys_out,
    size_t *count_out)
{
    char **keys;
    size_t allocation_count;
    size_t i;

    if (keys_out == NULL || count_out == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    *keys_out = NULL;
    *count_out = 0;

    if (!dictionary_is_valid(dictionary)) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    if (dictionary->count == SIZE_MAX) {
        return DICTIONARY_OVERFLOW;
    }

    allocation_count = dictionary->count + 1;

    if (allocation_count > SIZE_MAX / sizeof(*keys)) {
        return DICTIONARY_OVERFLOW;
    }

    keys = calloc(allocation_count, sizeof(*keys));
    if (keys == NULL) {
        return DICTIONARY_OUT_OF_MEMORY;
    }

    for (i = 0; i < dictionary->count; ++i) {
        keys[i] = duplicate_string(dictionary->entries[i].key);
        if (keys[i] == NULL) {
            while (i > 0) {
                --i;
                free(keys[i]);
            }

            free(keys);
            return DICTIONARY_OUT_OF_MEMORY;
        }
    }

    *keys_out = keys;
    *count_out = dictionary->count;

    return DICTIONARY_OK;
}

static void dictionary_free_keys(char **keys, size_t count)
{
    size_t i;

    if (keys == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(keys[i]);
    }

    free(keys);
}

static void dictionary_destroy(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return;
    }

    if (dictionary->entries != NULL) {
        size_t i;

        for (i = 0; i < dictionary->count; ++i) {
            free(dictionary->entries[i].key);
            free(dictionary->entries[i].value);
        }
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->count = 0;
    dictionary->capacity = 0;
}

static const char *dictionary_status_string(DictionaryStatus status)
{
    switch (status) {
        case DICTIONARY_OK:
            return "success";

        case DICTIONARY_INVALID_ARGUMENT:
            return "invalid argument";

        case DICTIONARY_OUT_OF_MEMORY:
            return "out of memory";

        case DICTIONARY_OVERFLOW:
            return "size overflow";

        default:
            return "unknown error";
    }
}

int main(void)
{
    Dictionary dictionary = {NULL, 0, 0};
    DictionaryStatus status;
    char **keys = NULL;
    size_t key_count = 0;
    size_t i;
    int result = EXIT_FAILURE;

    status = dictionary_put(&dictionary, "name", "Alice");
    if (status != DICTIONARY_OK) {
        goto cleanup;
    }

    status = dictionary_put(&dictionary, "age", "30");
    if (status != DICTIONARY_OK) {
        goto cleanup;
    }

    status = dictionary_put(&dictionary, "city", "London");
    if (status != DICTIONARY_OK) {
        goto cleanup;
    }

    status = dictionary_get_keys(&dictionary, &keys, &key_count);
    if (status != DICTIONARY_OK) {
        goto cleanup;
    }

    for (i = 0; i < key_count; ++i) {
        if (printf("%s\n", keys[i]) < 0) {
            status = DICTIONARY_INVALID_ARGUMENT;
            goto cleanup;
        }
    }

    result = EXIT_SUCCESS;

cleanup:
    if (result != EXIT_SUCCESS) {
        fprintf(stderr, "Error: %s\n", dictionary_status_string(status));
    }

    dictionary_free_keys(keys, key_count);
    dictionary_destroy(&dictionary);

    return result;
}