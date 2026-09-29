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
} Dictionary;

static char *duplicate_string(const char *source, size_t maximum_length)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || maximum_length == 0U) {
        return NULL;
    }

    terminator = memchr(source, '\0', maximum_length);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);

    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0U) {
        memcpy(copy, source, length);
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
}

static int dictionary_initialize(
    Dictionary *dictionary,
    const char *const keys[],
    const char *const values[],
    size_t count,
    size_t maximum_string_length)
{
    size_t index;

    if (dictionary == NULL ||
        maximum_string_length == 0U ||
        (count > 0U && (keys == NULL || values == NULL))) {
        return -1;
    }

    dictionary->entries = NULL;
    dictionary->count = 0U;

    if (count == 0U) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*dictionary->entries)) {
        return -1;
    }

    dictionary->entries = calloc(count, sizeof(*dictionary->entries));
    if (dictionary->entries == NULL) {
        return -1;
    }

    for (index = 0U; index < count; ++index) {
        char *key_copy;
        char *value_copy;

        if (keys[index] == NULL || values[index] == NULL) {
            dictionary_destroy(dictionary);
            return -1;
        }

        key_copy = duplicate_string(keys[index], maximum_string_length);
        if (key_copy == NULL) {
            dictionary_destroy(dictionary);
            return -1;
        }

        value_copy = duplicate_string(values[index], maximum_string_length);
        if (value_copy == NULL) {
            free(key_copy);
            dictionary_destroy(dictionary);
            return -1;
        }

        dictionary->entries[index].key = key_copy;
        dictionary->entries[index].value = value_copy;
        dictionary->count = index + 1U;
    }

    return 0;
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
    static const char *const keys[] = {
        "name",
        "language",
        "version"
    };
    static const char *const values[] = {
        "Example",
        "C",
        "17"
    };

    const size_t item_count = sizeof(keys) / sizeof(keys[0]);
    const size_t value_count = sizeof(values) / sizeof(values[0]);
    const size_t maximum_string_length = 1024U;
    const size_t index = 1U;
    const DictionaryEntry *entry;
    Dictionary dictionary = {NULL, 0U};

    if (item_count != value_count) {
        fputs("Dictionary key and value counts differ.\n", stderr);
        return EXIT_FAILURE;
    }

    if (dictionary_initialize(
            &dictionary,
            keys,
            values,
            item_count,
            maximum_string_length) != 0) {
        fputs("Failed to initialize dictionary.\n", stderr);
        return EXIT_FAILURE;
    }

    entry = dictionary_entry_at(&dictionary, index);
    if (entry == NULL) {
        fputs("Dictionary index is out of range.\n", stderr);
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    if (printf("%s: %s\n", entry->key, entry->value) < 0) {
        fputs("Failed to write output.\n", stderr);
        dictionary_destroy(&dictionary);
        return EXIT_FAILURE;
    }

    dictionary_destroy(&dictionary);
    return EXIT_SUCCESS;
}