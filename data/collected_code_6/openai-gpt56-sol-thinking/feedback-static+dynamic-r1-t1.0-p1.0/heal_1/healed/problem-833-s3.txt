#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    DICTIONARY_OK = 0,
    DICTIONARY_INVALID_ARGUMENT,
    DICTIONARY_OUT_OF_MEMORY,
    DICTIONARY_OVERFLOW,
    DICTIONARY_IO_ERROR
} DictionaryStatus;

typedef struct {
    char *key;
    size_t key_length;
    char *value;
    size_t value_length;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t count;
    size_t capacity;
} Dictionary;

static int bytes_contain_null(const char *data, size_t length)
{
    size_t i;

    for (i = 0; i < length; ++i) {
        if (data[i] == '\0') {
            return 1;
        }
    }

    return 0;
}

static int bytes_equal(
    const char *left,
    size_t left_length,
    const char *right,
    size_t right_length)
{
    size_t i;

    if (left_length != right_length) {
        return 0;
    }

    for (i = 0; i < left_length; ++i) {
        if (left[i] != right[i]) {
            return 0;
        }
    }

    return 1;
}

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
        const DictionaryEntry *entry = &dictionary->entries[i];

        if (entry->key == NULL || entry->value == NULL) {
            return 0;
        }

        if (entry->key_length == SIZE_MAX ||
            entry->value_length == SIZE_MAX) {
            return 0;
        }
    }

    return 1;
}

static DictionaryStatus duplicate_bytes(
    const char *source,
    size_t length,
    char **copy_out)
{
    char *copy;
    size_t i;

    if (source == NULL || copy_out == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    *copy_out = NULL;

    if (length == SIZE_MAX) {
        return DICTIONARY_OVERFLOW;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return DICTIONARY_OUT_OF_MEMORY;
    }

    for (i = 0; i < length; ++i) {
        copy[i] = source[i];
    }

    copy[length] = '\0';
    *copy_out = copy;
    return DICTIONARY_OK;
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
    size_t key_length,
    const char *value,
    size_t value_length)
{
    char *key_copy = NULL;
    char *value_copy = NULL;
    DictionaryStatus status;
    size_t i;

    if (!dictionary_is_valid(dictionary) ||
        key == NULL ||
        value == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    if (key_length == SIZE_MAX || value_length == SIZE_MAX) {
        return DICTIONARY_OVERFLOW;
    }

    if (bytes_contain_null(key, key_length) ||
        bytes_contain_null(value, value_length)) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    for (i = 0; i < dictionary->count; ++i) {
        DictionaryEntry *entry = &dictionary->entries[i];

        if (bytes_equal(
                entry->key,
                entry->key_length,
                key,
                key_length)) {
            status = duplicate_bytes(value, value_length, &value_copy);
            if (status != DICTIONARY_OK) {
                return status;
            }

            free(entry->value);
            entry->value = value_copy;
            entry->value_length = value_length;
            return DICTIONARY_OK;
        }
    }

    if (dictionary->count == SIZE_MAX) {
        return DICTIONARY_OVERFLOW;
    }

    status = duplicate_bytes(key, key_length, &key_copy);
    if (status != DICTIONARY_OK) {
        return status;
    }

    status = duplicate_bytes(value, value_length, &value_copy);
    if (status != DICTIONARY_OK) {
        free(key_copy);
        return status;
    }

    status = dictionary_reserve(dictionary, dictionary->count + 1);
    if (status != DICTIONARY_OK) {
        free(value_copy);
        free(key_copy);
        return status;
    }

    dictionary->entries[dictionary->count].key = key_copy;
    dictionary->entries[dictionary->count].key_length = key_length;
    dictionary->entries[dictionary->count].value = value_copy;
    dictionary->entries[dictionary->count].value_length = value_length;
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
        DictionaryStatus status = duplicate_bytes(
            dictionary->entries[i].key,
            dictionary->entries[i].key_length,
            &keys[i]);

        if (status != DICTIONARY_OK) {
            while (i > 0) {
                --i;
                free(keys[i]);
            }

            free(keys);
            return status;
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
        case DICTIONARY_IO_ERROR:
            return "I/O error";
        default:
            return "unknown error";
    }
}

int main(void)
{
    Dictionary dictionary = {NULL, 0, 0};
    DictionaryStatus status = DICTIONARY_OK;
    char **keys = NULL;
    size_t key_count = 0;
    size_t i;
    int result = EXIT_FAILURE;

    status = dictionary_put(
        &dictionary,
        "name",
        sizeof("name") - 1,
        "Alice",
        sizeof("Alice") - 1);
    if (status != DICTIONARY_OK) {
        goto cleanup;
    }

    status = dictionary_put(
        &dictionary,
        "age",
        sizeof("age") - 1,
        "30",
        sizeof("30") - 1);
    if (status != DICTIONARY_OK) {
        goto cleanup;
    }

    status = dictionary_put(
        &dictionary,
        "city",
        sizeof("city") - 1,
        "London",
        sizeof("London") - 1);
    if (status != DICTIONARY_OK) {
        goto cleanup;
    }

    status = dictionary_get_keys(&dictionary, &keys, &key_count);
    if (status != DICTIONARY_OK) {
        goto cleanup;
    }

    for (i = 0; i < key_count; ++i) {
        if (fputs(keys[i], stdout) == EOF ||
            fputc('\n', stdout) == EOF) {
            status = DICTIONARY_IO_ERROR;
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