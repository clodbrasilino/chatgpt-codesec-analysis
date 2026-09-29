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
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->size = 0U;
}

static bool dictionary_create(
    Dictionary *dictionary,
    const char *const keys[],
    const size_t key_lengths[],
    const char *const values[],
    const size_t value_lengths[],
    size_t size)
{
    size_t index;

    if (dictionary == NULL) {
        return false;
    }

    dictionary->entries = NULL;
    dictionary->size = 0U;

    if (size == 0U) {
        return true;
    }

    if (keys == NULL || key_lengths == NULL ||
        values == NULL || value_lengths == NULL ||
        size > SIZE_MAX / sizeof(*dictionary->entries)) {
        return false;
    }

    dictionary->entries = calloc(size, sizeof(*dictionary->entries));
    if (dictionary->entries == NULL) {
        return false;
    }

    dictionary->size = size;

    for (index = 0U; index < size; ++index) {
        if (keys[index] == NULL || values[index] == NULL) {
            dictionary_destroy(dictionary);
            return false;
        }

        dictionary->entries[index].key =
            duplicate_string(keys[index], key_lengths[index]);
        if (dictionary->entries[index].key == NULL) {
            dictionary_destroy(dictionary);
            return false;
        }

        dictionary->entries[index].value =
            duplicate_string(values[index], value_lengths[index]);
        if (dictionary->entries[index].value == NULL) {
            dictionary_destroy(dictionary);
            return false;
        }
    }

    return true;
}

static bool dictionary_all_values_same(const Dictionary *dictionary)
{
    size_t index;
    const char *first_value;

    if (dictionary == NULL ||
        (dictionary->size > 0U && dictionary->entries == NULL)) {
        return false;
    }

    if (dictionary->size <= 1U) {
        return true;
    }

    first_value = dictionary->entries[0].value;
    if (first_value == NULL) {
        return false;
    }

    for (index = 1U; index < dictionary->size; ++index) {
        if (dictionary->entries[index].value == NULL ||
            strcmp(first_value, dictionary->entries[index].value) != 0) {
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
    static const size_t key_lengths[] = {
        sizeof("first") - 1U,
        sizeof("second") - 1U,
        sizeof("third") - 1U
    };
    static const char *const values[] = {
        "same",
        "same",
        "same"
    };
    static const size_t value_lengths[] = {
        sizeof("same") - 1U,
        sizeof("same") - 1U,
        sizeof("same") - 1U
    };

    Dictionary dictionary = {NULL, 0U};
    int result;

    if (!dictionary_create(
            &dictionary,
            keys,
            key_lengths,
            values,
            value_lengths,
            sizeof(keys) / sizeof(keys[0]))) {
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