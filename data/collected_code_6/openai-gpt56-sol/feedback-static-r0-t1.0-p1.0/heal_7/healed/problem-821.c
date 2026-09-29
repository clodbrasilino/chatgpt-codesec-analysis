#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static char *duplicate_string_n(const char *source, size_t length)
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

static char *duplicate_bounded_string(const char *source, size_t limit)
{
    const char *terminator;

    if (source == NULL || limit == 0U) {
        return NULL;
    }

    terminator = memchr(source, '\0', limit);
    if (terminator == NULL) {
        return NULL;
    }

    return duplicate_string_n(source, (size_t)(terminator - source));
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0U; i < dictionary->size; ++i) {
        free(dictionary->entries[i].key);
        free(dictionary->entries[i].value);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->size = 0U;
    dictionary->capacity = 0U;
}

static int dictionary_initialize(Dictionary *dictionary, size_t capacity)
{
    if (dictionary == NULL) {
        return -1;
    }

    dictionary->entries = NULL;
    dictionary->size = 0U;
    dictionary->capacity = 0U;

    if (capacity == 0U) {
        return 0;
    }

    if (capacity > SIZE_MAX / sizeof(*dictionary->entries)) {
        return -1;
    }

    dictionary->entries = calloc(capacity, sizeof(*dictionary->entries));
    if (dictionary->entries == NULL) {
        return -1;
    }

    dictionary->capacity = capacity;
    return 0;
}

static int dictionary_reserve(Dictionary *dictionary, size_t capacity)
{
    Entry *new_entries;

    if (dictionary == NULL) {
        return -1;
    }

    if (capacity <= dictionary->capacity) {
        return 0;
    }

    if (capacity > SIZE_MAX / sizeof(*dictionary->entries)) {
        return -1;
    }

    new_entries = realloc(dictionary->entries,
                          capacity * sizeof(*dictionary->entries));
    if (new_entries == NULL) {
        return -1;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = capacity;
    return 0;
}

static size_t dictionary_find_n(const Dictionary *dictionary,
                                const char *key,
                                size_t key_length)
{
    size_t i;

    if (dictionary == NULL || key == NULL) {
        return SIZE_MAX;
    }

    for (i = 0U; i < dictionary->size; ++i) {
        if (dictionary->entries[i].key_length == key_length &&
            memcmp(dictionary->entries[i].key, key, key_length) == 0) {
            return i;
        }
    }

    return SIZE_MAX;
}