#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
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

static bool dictionary_find(
    const Dictionary *dictionary,
    const char *key,
    size_t *index)
{
    size_t i;

    if (dictionary == NULL || key == NULL) {
        return false;
    }

    for (i = 0; i < dictionary->size; ++i) {
        if (strcmp(dictionary->entries[i].key, key) == 0) {
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
    int64_t value)
{
    size_t index;
    char *key_copy;

    if (dictionary == NULL || key == NULL) {
        return false;
    }

    if (dictionary_find(dictionary, key, &index)) {
        dictionary->entries[index].value = value;
        return true;
    }

    key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        return false;
    }

    if (!dictionary_reserve(dictionary)) {
        free(key_copy);
        return false;
    }

    dictionary->entries[dictionary->size].key = key_copy;
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
    int64_t value)
{
    size_t index;
    int64_t sum;

    if (dictionary == NULL || key == NULL) {
        return false;
    }

    if (!dictionary_find(dictionary, key, &index)) {
        return dictionary_put(dictionary, key, value);
    }

    if (!add_int64(dictionary->entries[index].value, value, &sum)) {
        return false;
    }

    dictionary->entries[index].value = sum;
    return true;
}

Dictionary *combine_dictionaries(
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
                first->entries[i].value)) {
            dictionary_destroy(combined);
            return NULL;
        }
    }

    for (i = 0; i < second->size; ++i) {
        if (!dictionary_add(
                combined,
                second->entries[i].key,
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
        if (printf(
                "%s: %" PRId64 "\n",
                dictionary->entries[i].key,
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

    if (!dictionary_put(first, "apple", 3) ||
        !dictionary_put(first, "banana", 5) ||
        !dictionary_put(first, "orange", 7) ||
        !dictionary_put(second, "banana", 4) ||
        !dictionary_put(second, "orange", 2) ||
        !dictionary_put(second, "pear", 6)) {
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