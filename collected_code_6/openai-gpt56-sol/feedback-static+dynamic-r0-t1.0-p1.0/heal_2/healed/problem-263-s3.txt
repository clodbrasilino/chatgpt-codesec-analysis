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

static char *duplicate_string(const char *source, size_t source_size)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || source_size == 0) {
        return NULL;
    }

    terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);

    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0) {
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

static size_t dictionary_find(const Dictionary *dictionary,
                              const char *key,
                              size_t key_size)
{
    const char *terminator;
    size_t key_length;
    size_t i;

    if (dictionary == NULL || key == NULL || key_size == 0) {
        return SIZE_MAX;
    }

    terminator = memchr(key, '\0', key_size);
    if (terminator == NULL) {
        return SIZE_MAX;
    }

    key_length = (size_t)(terminator - key);

    for (i = 0; i < dictionary->size; ++i) {
        size_t stored_length = strlen(dictionary->entries[i].key);

        if (stored_length == key_length &&
            memcmp(dictionary->entries[i].key, key, key_length) == 0) {
            return i;
        }
    }

    return SIZE_MAX;
}

static int dictionary_set(Dictionary *dictionary,
                          const char *key,
                          size_t key_size,
                          const char *value,
                          size_t value_size)
{
    size_t index;
    char *key_copy;
    char *value_copy;

    if (dictionary == NULL || key == NULL || key_size == 0 ||
        value == NULL || value_size == 0) {
        return -1;
    }

    if (memchr(key, '\0', key_size) == NULL ||
        memchr(value, '\0', value_size) == NULL) {
        return -1;
    }

    index = dictionary_find(dictionary, key, key_size);

    value_copy = duplicate_string(value, value_size);
    if (value_copy == NULL) {
        return -1;
    }

    if (index != SIZE_MAX) {
        char *old_value = dictionary->entries[index].value;

        dictionary->entries[index].value = value_copy;
        free(old_value);
        return 0;
    }

    key_copy = duplicate_string(key, key_size);
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
    dictionary->entries[dictionary->size].value = value_copy;
    ++dictionary->size;

    return 0;
}

static int dictionary_copy(Dictionary *destination,
                           const Dictionary *source)
{
    Dictionary copy;
    size_t i;

    if (destination == NULL || source == NULL || destination == source) {
        return -1;
    }

    dictionary_init(&copy);

    if (dictionary_reserve(&copy, source->size) != 0) {
        return -1;
    }

    for (i = 0; i < source->size; ++i) {
        const char *key = source->entries[i].key;
        const char *value = source->entries[i].value;
        size_t key_length = strlen(key);
        size_t value_length = strlen(value);

        if (key_length == SIZE_MAX || value_length == SIZE_MAX ||
            dictionary_set(&copy,
                           key,
                           key_length + 1,
                           value,
                           value_length + 1) != 0) {
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
        result == first || result == second) {
        return -1;
    }

    dictionary_init(&merged);

    if (dictionary_copy(&merged, first) != 0) {
        return -1;
    }

    for (i = 0; i < second->size; ++i) {
        const char *key = second->entries[i].key;
        const char *value = second->entries[i].value;
        size_t key_length = strlen(key);
        size_t value_length = strlen(value);

        if (key_length == SIZE_MAX || value_length == SIZE_MAX ||
            dictionary_set(&merged,
                           key,
                           key_length + 1,
                           value,
                           value_length + 1) != 0) {
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

    if (dictionary == NULL) {
        return -1;
    }

    for (i = 0; i < dictionary->size; ++i) {
        if (printf("%s: %s\n",
                   dictionary->entries[i].key,
                   dictionary->entries[i].value) < 0) {
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