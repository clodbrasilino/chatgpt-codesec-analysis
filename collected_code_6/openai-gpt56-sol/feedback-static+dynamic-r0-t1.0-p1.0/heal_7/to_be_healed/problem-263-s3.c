#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static void dictionary_init(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return;
    }

    dictionary->entries = NULL;
    dictionary->size = 0;
    dictionary->capacity = 0;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0; i < dictionary->size; ++i) {
        free(dictionary->entries[i].key);
        free(dictionary->entries[i].value);
    }

    free(dictionary->entries);
    dictionary_init(dictionary);
}

static int validate_string(const char *string, size_t buffer_size,
                           size_t *length)
{
    const char *terminator;

    if (string == NULL || buffer_size == 0 || length == NULL) {
        return -1;
    }

    terminator = memchr(string, '\0', buffer_size);
    if (terminator == NULL) {
        return -1;
    }

    *length = (size_t)(terminator - string);
    return 0;
}

static char *duplicate_string(const char *source, size_t source_size,
                              size_t length)
{
    char *copy;
    size_t allocation_size;

    if (source == NULL || length > source_size || length == SIZE_MAX) {
        return NULL;
    }

    allocation_size = length + 1;
    copy = malloc(allocation_size);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static int dictionary_reserve(Dictionary *dictionary, size_t capacity)
{
    Entry *entries;

    if (dictionary == NULL) {
        return -1;
    }

    if (capacity <= dictionary->capacity) {
        return 0;
    }

    if (capacity > SIZE_MAX / sizeof(*entries)) {
        return -1;
    }

    entries = realloc(dictionary->entries, capacity * sizeof(*entries));
    if (entries == NULL) {
        return -1;
    }

    dictionary->entries = entries;
    dictionary->capacity = capacity;
    return 0;
}

static size_t dictionary_find_length(const Dictionary *dictionary,
                                     const char *key, size_t key_length)
{
    size_t i;

    if (dictionary == NULL || key == NULL) {
        return SIZE_MAX;
    }

    for (i = 0; i < dictionary->size; ++i) {
        const Entry *entry = &dictionary->entries[i];

        if (entry->key != NULL &&
            entry->key_length == key_length &&
            (key_length == 0 ||
             memcmp(entry->key, key, key_length) == 0)) {
            return i;
        }
    }

    return SIZE_MAX;
}

static int dictionary_set_length(Dictionary *dictionary,
                                 const char *key, size_t key_size,
                                 size_t key_length,
                                 const char *value, size_t value_size,
                                 size_t value_length)
{
    size_t index;
    char *key_copy;
    char *value_copy;

    if (dictionary == NULL || key == NULL || value == NULL ||
        key_length == SIZE_MAX || value_length == SIZE_MAX ||
        key_length > key_size || value_length > value_size ||
        dictionary->size > dictionary->capacity ||
        (dictionary->size != 0 && dictionary->entries == NULL)) {
        return -1;
    }

    index = dictionary_find_length(dictionary, key, key_length);

    value_copy = duplicate_string(value, value_size, value_length);
    if (value_copy == NULL) {
        return -1;
    }

    if (index != SIZE_MAX) {
        Entry *entry = &dictionary->entries[index];
        char *old_value = entry->value;

        entry->value = value_copy;
        entry->value_length = value_length;
        free(old_value);
        return 0;
    }

    key_copy = duplicate_string(key, key_size, key_length);
    if (key_copy == NULL) {
        free(value_copy);
        return -1;
    }

    if (dictionary->size == dictionary->capacity) {
        size_t new_capacity;

        if (dictionary->capacity == 0) {
            new_capacity = 4;
        } else {
            if (dictionary->capacity > SIZE_MAX / 2) {
                free(key_copy);
                free(value_copy);
                return -1;
            }

            new_capacity = dictionary->capacity * 2;
        }

        if (dictionary_reserve(dictionary, new_capacity) != 0) {
            free(key_copy);
            free(value_copy);
            return -1;
        }
    }

    dictionary->entries[dictionary->size].key = key_copy;
    dictionary->entries[dictionary->size].key_length = key_length;
    dictionary->entries[dictionary->size].value = value_copy;
    dictionary->entries[dictionary->size].value_length = value_length;
    ++dictionary->size;

    return 0;
}

static int dictionary_set(Dictionary *dictionary,
                          const char *key, size_t key_size,
                          const char *value, size_t value_size)
{
    size_t key_length;
    size_t value_length;

    if (validate_string(key, key_size, &key_length) != 0 ||
        validate_string(value, value_size, &value_length) != 0) {
        return -1;
    }

    return dictionary_set_length(dictionary,
                                 key, key_size, key_length,
                                 value, value_size, value_length);
}

static int dictionary_copy(Dictionary *destination,
                           const Dictionary *source)
{
    Dictionary copy;
    size_t i;

    if (destination == NULL || source == NULL || destination == source ||
        source->size > source->capacity ||
        (source->size != 0 && source->entries == NULL)) {
        return -1;
    }

    dictionary_init(&copy);

    if (dictionary_reserve(&copy, source->size) != 0) {
        return -1;
    }

    for (i = 0; i < source->size; ++i) {
        const Entry *entry = &source->entries[i];

        if (entry->key == NULL || entry->value == NULL ||
            entry->key_length == SIZE_MAX ||
            entry->value_length == SIZE_MAX ||
            dictionary_set_length(&copy,
                                  entry->key, entry->key_length + 1,
                                  entry->key_length,
                                  entry->value, entry->value_length + 1,
                                  entry->value_length) != 0) {
            dictionary_destroy(&copy);
            return -1;
        }
    }

    dictionary_destroy(destination);
    *destination = copy;
    return 0;
}

static int dictionary_merge(Dictionary *result,
                            const Dictionary *first,
                            const Dictionary *second)
{
    Dictionary merged;
    size_t i;

    if (result == NULL || first == NULL || second == NULL ||
        result == first || result == second ||
        first->size > first->capacity ||
        second->size > second->capacity ||
        (first->size != 0 && first->entries == NULL) ||
        (second->size != 0 && second->entries == NULL)) {
        return -1;
    }

    dictionary_init(&merged);

    if (dictionary_copy(&merged, first) != 0) {
        return -1;
    }

    for (i = 0; i < second->size; ++i) {
        const Entry *entry = &second->entries[i];

        if (entry->key == NULL || entry->value == NULL ||
            entry->key_length == SIZE_MAX ||
            entry->value_length == SIZE_MAX ||
            dictionary_set_length(&merged,
                                  entry->key, entry->key_length + 1,
                                  entry->key_length,
                                  entry->value, entry->value_length + 1,
                                  entry->value_length) != 0) {
            dictionary_destroy(&merged);
            return -1;
        }
    }

    dictionary_destroy(result);
    *result = merged;
    return 0;
}

static int dictionary_print(const Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL ||
        dictionary->size > dictionary->capacity ||
        (dictionary->size != 0 && dictionary->entries == NULL)) {
        return -1;
    }

    for (i = 0; i < dictionary->size; ++i) {
        const Entry *entry = &dictionary->entries[i];

        if (entry->key == NULL || entry->value == NULL) {
            return -1;
        }

        if (fwrite(entry->key, 1, entry->key_length, stdout) !=
                entry->key_length ||
            fputs(": ", stdout) == EOF ||
            fwrite(entry->value, 1, entry->value_length, stdout) !=
                entry->value_length ||
            fputc('\n', stdout) == EOF) {
            return -1;
        }
    }

    return 0;
}

#define DICTIONARY_SET_LITERAL(dictionary, key, value) \
    dictionary_set((dictionary), (key), sizeof(key), (value), sizeof(value))

int main(void)
{
    Dictionary first;
    Dictionary second;
    Dictionary merged;
    int status = EXIT_FAILURE;

    dictionary_init(&first);
    dictionary_init(&second);
    dictionary_init(&merged);

    if (DICTIONARY_SET_LITERAL(&first, "name", "Alice") != 0 ||
        DICTIONARY_SET_LITERAL(&first, "city", "London") != 0 ||
        DICTIONARY_SET_LITERAL(&second, "city", "Paris") != 0 ||
        DICTIONARY_SET_LITERAL(&second, "role", "Developer") != 0) {
        fputs("Failed to create dictionaries.\n", stderr);
        goto cleanup;
    }

    if (dictionary_merge(&merged, &first, &second) != 0) {
        fputs("Failed to merge dictionaries.\n", stderr);
        goto cleanup;
    }

    if (dictionary_print(&merged) != 0) {
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