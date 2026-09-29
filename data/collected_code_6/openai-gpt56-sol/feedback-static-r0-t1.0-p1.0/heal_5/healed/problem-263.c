#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char *key;
    size_t key_length;
    char *value;
    size_t value_length;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static bool duplicate_string(const char *source, size_t source_length, char **copy)
{
    char *buffer;

    if (source == NULL || copy == NULL) {
        return false;
    }

    *copy = NULL;

    if (source_length == SIZE_MAX) {
        return false;
    }

    buffer = malloc(source_length + 1U);
    if (buffer == NULL) {
        return false;
    }

    if (source_length > 0U) {
        memcpy(buffer, source, source_length);
    }

    buffer[source_length] = '\0';
    *copy = buffer;
    return true;
}

static bool dictionary_init(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return false;
    }

    dictionary->entries = NULL;
    dictionary->size = 0U;
    dictionary->capacity = 0U;
    return true;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    if (dictionary->entries != NULL) {
        for (i = 0U; i < dictionary->size; ++i) {
            free(dictionary->entries[i].key);
            free(dictionary->entries[i].value);
        }
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->size = 0U;
    dictionary->capacity = 0U;
}

static size_t dictionary_find(
    const Dictionary *dictionary,
    const char *key,
    size_t key_length)
{
    size_t i;

    if (dictionary == NULL || key == NULL) {
        return SIZE_MAX;
    }

    for (i = 0U; i < dictionary->size; ++i) {
        const Entry *entry = &dictionary->entries[i];

        if (entry->key_length == key_length &&
            (key_length == 0U ||
             memcmp(entry->key, key, key_length) == 0)) {
            return i;
        }
    }

    return SIZE_MAX;
}

static bool dictionary_reserve(Dictionary *dictionary, size_t capacity)
{
    Entry *new_entries;

    if (dictionary == NULL) {
        return false;
    }

    if (capacity <= dictionary->capacity) {
        return true;
    }

    if (capacity > SIZE_MAX / sizeof(*dictionary->entries)) {
        return false;
    }

    new_entries = realloc(
        dictionary->entries,
        capacity * sizeof(*dictionary->entries));

    if (new_entries == NULL) {
        return false;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = capacity;
    return true;
}

static bool dictionary_set_n(
    Dictionary *dictionary,
    const char *key,
    size_t key_length,
    const char *value,
    size_t value_length)
{
    size_t index;
    char *new_key = NULL;
    char *new_value = NULL;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return false;
    }

    index = dictionary_find(dictionary, key, key_length);

    if (index != SIZE_MAX) {
        if (!duplicate_string(value, value_length, &new_value)) {
            return false;
        }

        free(dictionary->entries[index].value);
        dictionary->entries[index].value = new_value;
        dictionary->entries[index].value_length = value_length;
        return true;
    }

    if (dictionary->size == dictionary->capacity) {
        size_t new_capacity;

        if (dictionary->capacity == 0U) {
            new_capacity = 4U;
        } else {
            if (dictionary->capacity > SIZE_MAX / 2U) {
                return false;
            }

            new_capacity = dictionary->capacity * 2U;
        }

        if (!dictionary_reserve(dictionary, new_capacity)) {
            return false;
        }
    }

    if (!duplicate_string(key, key_length, &new_key)) {
        return false;
    }

    if (!duplicate_string(value, value_length, &new_value)) {
        free(new_key);
        return false;
    }

    dictionary->entries[dictionary->size].key = new_key;
    dictionary->entries[dictionary->size].key_length = key_length;
    dictionary->entries[dictionary->size].value = new_value;
    dictionary->entries[dictionary->size].value_length = value_length;
    ++dictionary->size;

    return true;
}

#define DICTIONARY_SET(dictionary, key, value) \
    dictionary_set_n(                          \
        (dictionary),                          \
        (key),                                 \
        sizeof(key) - 1U,                      \
        (value),                               \
        sizeof(value) - 1U)

static bool dictionary_merge(
    const Dictionary *first,
    const Dictionary *second,
    Dictionary *result)
{
    Dictionary merged;
    size_t required_capacity;
    size_t i;

    if (first == NULL || second == NULL || result == NULL ||
        result == first || result == second) {
        return false;
    }

    if (!dictionary_init(&merged)) {
        return false;
    }

    if (first->size > SIZE_MAX - second->size) {
        return false;
    }

    required_capacity = first->size + second->size;

    if (!dictionary_reserve(&merged, required_capacity)) {
        dictionary_destroy(&merged);
        return false;
    }

    for (i = 0U; i < first->size; ++i) {
        const Entry *entry = &first->entries[i];

        if (!dictionary_set_n(
                &merged,
                entry->key,
                entry->key_length,
                entry->value,
                entry->value_length)) {
            dictionary_destroy(&merged);
            return false;
        }
    }

    for (i = 0U; i < second->size; ++i) {
        const Entry *entry = &second->entries[i];

        if (!dictionary_set_n(
                &merged,
                entry->key,
                entry->key_length,
                entry->value,
                entry->value_length)) {
            dictionary_destroy(&merged);
            return false;
        }
    }

    dictionary_destroy(result);
    *result = merged;
    return true;
}

static bool write_bytes(const char *data, size_t length, FILE *stream)
{
    size_t written = 0U;

    if (data == NULL || stream == NULL) {
        return false;
    }

    while (written < length) {
        size_t count = fwrite(data + written, 1U, length - written, stream);

        if (count == 0U) {
            return false;
        }

        written += count;
    }

    return true;
}

static bool dictionary_print(const Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return false;
    }

    for (i = 0U; i < dictionary->size; ++i) {
        const Entry *entry = &dictionary->entries[i];

        if (!write_bytes(entry->key, entry->key_length, stdout) ||
            !write_bytes(": ", 2U, stdout) ||
            !write_bytes(entry->value, entry->value_length, stdout) ||
            !write_bytes("\n", 1U, stdout)) {
            return false;
        }
    }

    return fflush(stdout) == 0;
}

int main(void)
{
    Dictionary first;
    Dictionary second;
    Dictionary merged;
    int status = EXIT_FAILURE;

    if (!dictionary_init(&first)) {
        return EXIT_FAILURE;
    }

    if (!dictionary_init(&second)) {
        dictionary_destroy(&first);
        return EXIT_FAILURE;
    }

    if (!dictionary_init(&merged)) {
        dictionary_destroy(&second);
        dictionary_destroy(&first);
        return EXIT_FAILURE;
    }

    if (!DICTIONARY_SET(&first, "name", "Alice") ||
        !DICTIONARY_SET(&first, "city", "Paris") ||
        !DICTIONARY_SET(&second, "city", "London") ||
        !DICTIONARY_SET(&second, "role", "Developer")) {
        fputs("Failed to create dictionaries.\n", stderr);
        goto cleanup;
    }

    if (!dictionary_merge(&first, &second, &merged)) {
        fputs("Failed to merge dictionaries.\n", stderr);
        goto cleanup;
    }

    if (!dictionary_print(&merged)) {
        fputs("Failed to print dictionary.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(&merged);
    dictionary_destroy(&second);
    dictionary_destroy(&first);
    return status;
}