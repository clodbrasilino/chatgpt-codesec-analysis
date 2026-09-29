#include <stdbool.h>
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
    size_t size;
} Dictionary;

static char *duplicate_string(const char *source, size_t max_length)
{
    const char *terminator;
    size_t length;
    size_t allocation_size;
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

    allocation_size = length + 1U;
    copy = malloc(allocation_size);
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

    if (dictionary->entries != NULL) {
        for (index = 0U; index < dictionary->size; ++index) {
            free(dictionary->entries[index].key);
            free(dictionary->entries[index].value);
        }

        free(dictionary->entries);
    }

    dictionary->entries = NULL;
    dictionary->size = 0U;
}

static bool dictionary_create(
    Dictionary *dictionary,
    const char *const keys[],
    const char *const values[],
    size_t size,
    size_t max_string_length)
{
    DictionaryEntry *entries;
    size_t index;

    if (dictionary == NULL) {
        return false;
    }

    dictionary->entries = NULL;
    dictionary->size = 0U;

    if (size == 0U) {
        return true;
    }

    if (keys == NULL || values == NULL || max_string_length == 0U) {
        return false;
    }

    if (size > SIZE_MAX / sizeof(*entries)) {
        return false;
    }

    entries = calloc(size, sizeof(*entries));
    if (entries == NULL) {
        return false;
    }

    dictionary->entries = entries;
    dictionary->size = size;

    for (index = 0U; index < size; ++index) {
        if (keys[index] == NULL || values[index] == NULL) {
            dictionary_destroy(dictionary);
            return false;
        }

        entries[index].key = duplicate_string(keys[index], max_string_length);
        if (entries[index].key == NULL) {
            dictionary_destroy(dictionary);
            return false;
        }

        entries[index].value =
            duplicate_string(values[index], max_string_length);
        if (entries[index].value == NULL) {
            dictionary_destroy(dictionary);
            return false;
        }
    }

    return true;
}

static bool dictionary_all_values_same(const Dictionary *dictionary)
{
    const char *first_value;
    size_t index;

    if (dictionary == NULL) {
        return false;
    }

    if (dictionary->size == 0U) {
        return true;
    }

    if (dictionary->entries == NULL ||
        dictionary->entries[0].value == NULL) {
        return false;
    }

    first_value = dictionary->entries[0].value;

    for (index = 1U; index < dictionary->size; ++index) {
        const char *value = dictionary->entries[index].value;

        if (value == NULL || strcmp(first_value, value) != 0) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    static const char *const keys[] = {
        "first",
        "second",
        "third"
    };
    static const char *const values[] = {
        "same",
        "same",
        "same"
    };
    Dictionary dictionary = {NULL, 0U};
    const size_t key_count = sizeof(keys) / sizeof(keys[0]);
    const size_t value_count = sizeof(values) / sizeof(values[0]);
    int result;

    if (key_count != value_count) {
        fputs("Mismatched key and value counts.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!dictionary_create(
            &dictionary, keys, values, key_count, 1024U)) {
        fputs("Failed to create dictionary.\n", stderr);
        return EXIT_FAILURE;
    }

    result = printf(
        "%s\n",
        dictionary_all_values_same(&dictionary)
            ? "All values are the same."
            : "Values are not all the same.");

    dictionary_destroy(&dictionary);

    return result < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}