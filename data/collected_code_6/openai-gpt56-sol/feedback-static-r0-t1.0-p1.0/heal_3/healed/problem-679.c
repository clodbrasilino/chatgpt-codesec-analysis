#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t count;
    size_t capacity;
} Dictionary;

static char *duplicate_string(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0U) {
        memmove(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return;
    }

    for (index = 0U; index < dictionary->count; ++index) {
        free(dictionary->entries[index].key);
        free(dictionary->entries[index].value);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->count = 0U;
    dictionary->capacity = 0U;
}

static int dictionary_reserve(Dictionary *dictionary, size_t capacity)
{
    DictionaryEntry *new_entries;

    if (dictionary == NULL) {
        return 0;
    }

    if (capacity <= dictionary->capacity) {
        return 1;
    }

    if (capacity > SIZE_MAX / sizeof(*new_entries)) {
        return 0;
    }

    new_entries = realloc(
        dictionary->entries,
        capacity * sizeof(*new_entries)
    );
    if (new_entries == NULL) {
        return 0;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = capacity;
    return 1;
}

static int dictionary_add_n(
    Dictionary *dictionary,
    const char *key,
    size_t key_length,
    const char *value,
    size_t value_length)
{
    char *key_copy;
    char *value_copy;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return 0;
    }

    if (key_length == SIZE_MAX || value_length == SIZE_MAX) {
        return 0;
    }

    if (dictionary->count == dictionary->capacity) {
        size_t new_capacity;

        if (dictionary->capacity == 0U) {
            new_capacity = 4U;
        } else {
            if (dictionary->capacity > SIZE_MAX / 2U) {
                return 0;
            }

            new_capacity = dictionary->capacity * 2U;
        }

        if (!dictionary_reserve(dictionary, new_capacity)) {
            return 0;
        }
    }

    key_copy = duplicate_string(key, key_length);
    if (key_copy == NULL) {
        return 0;
    }

    value_copy = duplicate_string(value, value_length);
    if (value_copy == NULL) {
        free(key_copy);
        return 0;
    }

    dictionary->entries[dictionary->count].key = key_copy;
    dictionary->entries[dictionary->count].value = value_copy;
    ++dictionary->count;

    return 1;
}

static const DictionaryEntry *dictionary_entry_at(
    const Dictionary *dictionary,
    size_t index)
{
    if (dictionary == NULL ||
        dictionary->entries == NULL ||
        index >= dictionary->count) {
        return NULL;
    }

    return &dictionary->entries[index];
}

int main(void)
{
    Dictionary dictionary = {NULL, 0U, 0U};
    const DictionaryEntry *entry;
    int status = EXIT_FAILURE;

    if (!dictionary_add_n(
            &dictionary,
            "language",
            sizeof("language") - 1U,
            "C",
            sizeof("C") - 1U) ||
        !dictionary_add_n(
            &dictionary,
            "standard",
            sizeof("standard") - 1U,
            "C17",
            sizeof("C17") - 1U) ||
        !dictionary_add_n(
            &dictionary,
            "purpose",
            sizeof("purpose") - 1U,
            "systems programming",
            sizeof("systems programming") - 1U)) {
        fputs("Failed to create dictionary.\n", stderr);
        goto cleanup;
    }

    entry = dictionary_entry_at(&dictionary, 1U);
    if (entry == NULL) {
        fputs("Dictionary index is out of range.\n", stderr);
        goto cleanup;
    }

    if (printf("%s: %s\n", entry->key, entry->value) < 0) {
        fputs("Failed to write output.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(&dictionary);
    return status;
}