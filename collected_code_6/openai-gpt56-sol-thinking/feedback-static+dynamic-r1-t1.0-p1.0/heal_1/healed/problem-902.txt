#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    size_t key_length;
    int64_t value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static Dictionary *dictionary_create(void)
{
    Dictionary *dictionary = malloc(sizeof(*dictionary));

    if (dictionary == NULL) {
        return NULL;
    }

    dictionary->entries = NULL;
    dictionary->size = 0;
    dictionary->capacity = 0;

    return dictionary;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0; i < dictionary->size; ++i) {
        free(dictionary->entries[i].key);
    }

    free(dictionary->entries);
    free(dictionary);
}

static char *duplicate_bytes(const char *source, size_t length)
{
    char *copy;
    size_t i;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    for (i = 0; i < length; ++i) {
        copy[i] = source[i];
    }

    copy[length] = '\0';
    return copy;
}

static bool dictionary_find(
    const Dictionary *dictionary,
    const char *key,
    size_t key_length,
    size_t *index)
{
    size_t i;

    if (dictionary == NULL || key == NULL) {
        return false;
    }

    for (i = 0; i < dictionary->size; ++i) {
        if (dictionary->entries[i].key_length == key_length &&
            (key_length == 0 ||
             memcmp(dictionary->entries[i].key, key, key_length) == 0)) {
            if (index != NULL) {
                *index = i;
            }
            return true;
        }
    }

    return false;
}

static bool dictionary_reserve(Dictionary *dictionary)
{
    size_t new_capacity;
    DictionaryEntry *new_entries;

    if (dictionary == NULL) {
        return false;
    }

    if (dictionary->size < dictionary->capacity) {
        return true;
    }

    if (dictionary->capacity == 0) {
        new_capacity = 8;
    } else {
        if (dictionary->capacity > SIZE_MAX / 2) {
            return false;
        }

        new_capacity = dictionary->capacity * 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*new_entries)) {
        return false;
    }

    new_entries = realloc(
        dictionary->entries,
        new_capacity * sizeof(*new_entries));

    if (new_entries == NULL) {
        return false;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = new_capacity;

    return true;
}

static bool dictionary_put(
    Dictionary *dictionary,
    const char *key,
    size_t key_length,
    int64_t value)
{
    size_t index;
    char *key_copy;

    if (dictionary == NULL || key == NULL) {
        return false;
    }

    if (dictionary_find(dictionary, key, key_length, &index)) {
        dictionary->entries[index].value = value;
        return true;
    }

    key_copy = duplicate_bytes(key, key_length);
    if (key_copy == NULL) {
        return false;
    }

    if (!dictionary_reserve(dictionary)) {
        free(key_copy);
        return false;
    }

    dictionary->entries[dictionary->size].key = key_copy;
    dictionary->entries[dictionary->size].key_length = key_length;
    dictionary->entries[dictionary->size].value = value;
    ++dictionary->size;

    return true;
}

static bool add_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if ((right > 0 && left > INT64_MAX - right) ||
        (right < 0 && left < INT64_MIN - right)) {
        return false;
    }

    *result = left + right;
    return true;
}

static bool dictionary_add(
    Dictionary *dictionary,
    const char *key,
    size_t key_length,
    int64_t value)
{
    size_t index;
    int64_t sum;

    if (dictionary == NULL || key == NULL) {
        return false;
    }

    if (!dictionary_find(dictionary, key, key_length, &index)) {
        return dictionary_put(dictionary, key, key_length, value);
    }

    if (!add_int64(dictionary->entries[index].value, value, &sum)) {
        return false;
    }

    dictionary->entries[index].value = sum;
    return true;
}

static Dictionary *combine_dictionaries(
    const Dictionary *first,
    const Dictionary *second)
{
    Dictionary *combined;
    size_t i;

    if (first == NULL || second == NULL) {
        return NULL;
    }

    combined = dictionary_create();
    if (combined == NULL) {
        return NULL;
    }

    for (i = 0; i < first->size; ++i) {
        if (!dictionary_put(
                combined,
                first->entries[i].key,
                first->entries[i].key_length,
                first->entries[i].value)) {
            dictionary_destroy(combined);
            return NULL;
        }
    }

    for (i = 0; i < second->size; ++i) {
        if (!dictionary_add(
                combined,
                second->entries[i].key,
                second->entries[i].key_length,
                second->entries[i].value)) {
            dictionary_destroy(combined);
            return NULL;
        }
    }

    return combined;
}

static bool dictionary_print(const Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return false;
    }

    for (i = 0; i < dictionary->size; ++i) {
        if (dictionary->entries[i].key_length > 0 &&
            fwrite(
                dictionary->entries[i].key,
                1,
                dictionary->entries[i].key_length,
                stdout) != dictionary->entries[i].key_length) {
            return false;
        }

        if (fputs(": ", stdout) == EOF) {
            return false;
        }

        if (printf(
                "%" PRId64 "\n",
                dictionary->entries[i].value) < 0) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    Dictionary *first = NULL;
    Dictionary *second = NULL;
    Dictionary *combined = NULL;
    int status = EXIT_FAILURE;

    first = dictionary_create();
    second = dictionary_create();

    if (first == NULL || second == NULL) {
        fputs("Failed to create dictionaries.\n", stderr);
        goto cleanup;
    }

    if (!dictionary_put(first, "apple", sizeof("apple") - 1, 3) ||
        !dictionary_put(first, "banana", sizeof("banana") - 1, 5) ||
        !dictionary_put(first, "orange", sizeof("orange") - 1, 7) ||
        !dictionary_put(second, "banana", sizeof("banana") - 1, 4) ||
        !dictionary_put(second, "orange", sizeof("orange") - 1, 2) ||
        !dictionary_put(second, "pear", sizeof("pear") - 1, 6)) {
        fputs("Failed to populate dictionaries.\n", stderr);
        goto cleanup;
    }

    combined = combine_dictionaries(first, second);
    if (combined == NULL) {
        fputs("Failed to combine dictionaries.\n", stderr);
        goto cleanup;
    }

    if (!dictionary_print(combined) || fflush(stdout) == EOF) {
        fputs("Failed to print the combined dictionary.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(combined);
    dictionary_destroy(second);
    dictionary_destroy(first);

    return status;
}