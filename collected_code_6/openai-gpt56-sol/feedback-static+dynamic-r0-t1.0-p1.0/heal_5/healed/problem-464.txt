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
    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    if (memchr(source, '\0', length) != NULL) {
        return NULL;
    }

    size_t allocation_size = length + 1U;
    char *copy = malloc(allocation_size);
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
    if (dictionary == NULL) {
        return;
    }

    for (size_t index = 0U;
         dictionary->entries != NULL && index < dictionary->size;
         ++index) {
        free(dictionary->entries[index].key);
        free(dictionary->entries[index].value);
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
    if (dictionary == NULL) {
        return false;
    }

    dictionary->entries = NULL;
    dictionary->size = 0U;

    if (size == 0U) {
        return true;
    }

    if (keys == NULL ||
        key_lengths == NULL ||
        values == NULL ||
        value_lengths == NULL ||
        size > SIZE_MAX / sizeof(DictionaryEntry)) {
        return false;
    }

    DictionaryEntry *entries = calloc(size, sizeof(*entries));
    if (entries == NULL) {
        return false;
    }

    dictionary->entries = entries;
    dictionary->size = size;

    for (size_t index = 0U; index < size; ++index) {
        if (keys[index] == NULL || values[index] == NULL) {
            dictionary_destroy(dictionary);
            return false;
        }

        entries[index].key =
            duplicate_string(keys[index], key_lengths[index]);

        if (entries[index].key == NULL) {
            dictionary_destroy(dictionary);
            return false;
        }

        entries[index].value =
            duplicate_string(values[index], value_lengths[index]);

        if (entries[index].value == NULL) {
            dictionary_destroy(dictionary);
            return false;
        }
    }

    return true;
}

static bool dictionary_all_values_same(const Dictionary *dictionary)
{
    if (dictionary == NULL ||
        (dictionary->size > 0U && dictionary->entries == NULL)) {
        return false;
    }

    if (dictionary->size <= 1U) {
        return true;
    }

    const char *first_value = dictionary->entries[0].value;
    if (first_value == NULL) {
        return false;
    }

    for (size_t index = 1U; index < dictionary->size; ++index) {
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
    const size_t count = sizeof(keys) / sizeof(keys[0]);

    if (!dictionary_create(
            &dictionary,
            keys,
            key_lengths,
            values,
            value_lengths,
            count)) {
        fputs("Failed to create dictionary.\n", stderr);
        return EXIT_FAILURE;
    }

    const char *message = dictionary_all_values_same(&dictionary)
        ? "All values are the same.\n"
        : "Values are not all the same.\n";

    int result = fputs(message, stdout);

    dictionary_destroy(&dictionary);

    return result == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}