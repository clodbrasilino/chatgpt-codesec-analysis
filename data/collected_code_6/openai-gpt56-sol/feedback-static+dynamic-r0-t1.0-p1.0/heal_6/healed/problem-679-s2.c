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

static char *duplicate_string(const char *source, size_t max_length)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || max_length == 0U) {
        return NULL;
    }

    terminator = memchr(source, '\0', max_length);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);

    if (length > SIZE_MAX - 1U) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0U) {
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    return copy;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return;
    }

    if (dictionary->entries != NULL) {
        for (size_t index = 0U; index < dictionary->count; ++index) {
            free(dictionary->entries[index].key);
            free(dictionary->entries[index].value);
        }

        free(dictionary->entries);
    }

    dictionary->entries = NULL;
    dictionary->count = 0U;
}

static int dictionary_initialize(
    Dictionary *dictionary,
    const char *const keys[],
    const char *const values[],
    size_t count,
    size_t max_string_length)
{
    Dictionary temporary = {NULL, 0U};

    if (dictionary == NULL ||
        max_string_length == 0U ||
        (count != 0U && (keys == NULL || values == NULL))) {
        return -1;
    }

    if (count == 0U) {
        dictionary_destroy(dictionary);
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*temporary.entries)) {
        return -1;
    }

    temporary.entries = calloc(count, sizeof(*temporary.entries));
    if (temporary.entries == NULL) {
        return -1;
    }

    for (size_t index = 0U; index < count; ++index) {
        if (keys[index] == NULL || values[index] == NULL) {
            dictionary_destroy(&temporary);
            return -1;
        }

        temporary.count = index + 1U;

        temporary.entries[index].key =
            duplicate_string(keys[index], max_string_length);
        if (temporary.entries[index].key == NULL) {
            dictionary_destroy(&temporary);
            return -1;
        }

        temporary.entries[index].value =
            duplicate_string(values[index], max_string_length);
        if (temporary.entries[index].value == NULL) {
            dictionary_destroy(&temporary);
            return -1;
        }
    }

    dictionary_destroy(dictionary);
    *dictionary = temporary;

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
    const size_t max_string_length = 1024U;
    const size_t index = 1U;
    Dictionary dictionary = {NULL, 0U};
    const DictionaryEntry *entry;

    if (item_count != value_count) {
        fputs("Dictionary input sizes do not match.\n", stderr);
        return EXIT_FAILURE;
    }

    if (dictionary_initialize(
            &dictionary,
            keys,
            values,
            item_count,
            max_string_length) != 0) {
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