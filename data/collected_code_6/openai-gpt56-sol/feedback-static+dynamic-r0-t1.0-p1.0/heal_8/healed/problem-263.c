#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STRING_LENGTH ((size_t)1048576U)

typedef struct {
    char *key;
    char *value;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static char *duplicate_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    length = strnlen(source, MAX_STRING_LENGTH);
    if (length == MAX_STRING_LENGTH) {
        return NULL;
    }

    if (length > SIZE_MAX - 1U) {
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

static bool dictionary_init(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return false;
    }

    dictionary->entries = NULL;
    dictionary->size = 0U;
    dictionary->capacity = 0U;

    return true;
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

static size_t dictionary_find(const Dictionary *dictionary, const char *key)
{
    size_t i;

    if (dictionary == NULL || key == NULL) {
        return SIZE_MAX;
    }

    for (i = 0U; i < dictionary->size; ++i) {
        if (dictionary->entries[i].key != NULL &&
            strcmp(dictionary->entries[i].key, key) == 0) {
            return i;
        }
    }

    return SIZE_MAX;
}

static bool dictionary_reserve(Dictionary *dictionary, size_t capacity)
{
    Entry *new_entries;
    size_t old_capacity;
    size_t additional_capacity;

    if (dictionary == NULL) {
        return false;
    }

    if (capacity <= dictionary->capacity) {
        return true;
    }

    if (capacity > SIZE_MAX / sizeof(*new_entries)) {
        return false;
    }

    old_capacity = dictionary->capacity;
    additional_capacity = capacity - old_capacity;

    new_entries = realloc(dictionary->entries,
                          capacity * sizeof(*new_entries));
    if (new_entries == NULL) {
        return false;
    }

    if (additional_capacity > 0U) {
        memset(new_entries + old_capacity, 0,
               additional_capacity * sizeof(*new_entries));
    }

    dictionary->entries = new_entries;
    dictionary->capacity = capacity;

    return true;
}

static bool dictionary_set(Dictionary *dictionary,
                           const char *key,
                           const char *value)
{
    size_t index;
    char *new_key;
    char *new_value;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return false;
    }

    index = dictionary_find(dictionary, key);
    if (index != SIZE_MAX) {
        new_value = duplicate_string(value);
        if (new_value == NULL) {
            return false;
        }

        free(dictionary->entries[index].value);
        dictionary->entries[index].value = new_value;
        return true;
    }

    if (dictionary->size == dictionary->capacity) {
        size_t new_capacity;

        if (dictionary->capacity == 0U) {
            new_capacity = 4U;
        } else {
            if (dictionary->capacity > SIZE_MAX / 2U) {
                return false;
            }
            new_capacity = dictionary->capacity * 2U;
        }

        if (!dictionary_reserve(dictionary, new_capacity)) {
            return false;
        }
    }

    new_key = duplicate_string(key);
    if (new_key == NULL) {
        return false;
    }

    new_value = duplicate_string(value);
    if (new_value == NULL) {
        free(new_key);
        return false;
    }

    dictionary->entries[dictionary->size].key = new_key;
    dictionary->entries[dictionary->size].value = new_value;
    ++dictionary->size;

    return true;
}

static bool dictionary_merge(const Dictionary *first,
                             const Dictionary *second,
                             Dictionary *result)
{
    Dictionary merged;
    size_t required_capacity;
    size_t i;

    if (first == NULL || second == NULL || result == NULL ||
        result == first || result == second) {
        return false;
    }

    if (first->size > SIZE_MAX - second->size) {
        return false;
    }

    if (!dictionary_init(&merged)) {
        return false;
    }

    required_capacity = first->size + second->size;

    if (required_capacity > 0U &&
        !dictionary_reserve(&merged, required_capacity)) {
        dictionary_destroy(&merged);
        return false;
    }

    for (i = 0U; i < first->size; ++i) {
        if (first->entries[i].key == NULL ||
            first->entries[i].value == NULL ||
            !dictionary_set(&merged,
                            first->entries[i].key,
                            first->entries[i].value)) {
            dictionary_destroy(&merged);
            return false;
        }
    }

    for (i = 0U; i < second->size; ++i) {
        if (second->entries[i].key == NULL ||
            second->entries[i].value == NULL ||
            !dictionary_set(&merged,
                            second->entries[i].key,
                            second->entries[i].value)) {
            dictionary_destroy(&merged);
            return false;
        }
    }

    dictionary_destroy(result);
    *result = merged;

    return true;
}

static bool dictionary_print(const Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return false;
    }

    for (i = 0U; i < dictionary->size; ++i) {
        if (dictionary->entries[i].key == NULL ||
            dictionary->entries[i].value == NULL) {
            return false;
        }

        if (printf("%s: %s\n",
                   dictionary->entries[i].key,
                   dictionary->entries[i].value) < 0) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    Dictionary first;
    Dictionary second;
    Dictionary merged;
    int status = EXIT_FAILURE;

    if (!dictionary_init(&first)) {
        return EXIT_FAILURE;
    }

    if (!dictionary_init(&second)) {
        dictionary_destroy(&first);
        return EXIT_FAILURE;
    }

    if (!dictionary_init(&merged)) {
        dictionary_destroy(&second);
        dictionary_destroy(&first);
        return EXIT_FAILURE;
    }

    if (!dictionary_set(&first, "name", "Alice") ||
        !dictionary_set(&first, "city", "Paris") ||
        !dictionary_set(&second, "city", "London") ||
        !dictionary_set(&second, "role", "Developer")) {
        fputs("Failed to create dictionaries.\n", stderr);
        goto cleanup;
    }

    if (!dictionary_merge(&first, &second, &merged)) {
        fputs("Failed to merge dictionaries.\n", stderr);
        goto cleanup;
    }

    if (!dictionary_print(&merged)) {
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