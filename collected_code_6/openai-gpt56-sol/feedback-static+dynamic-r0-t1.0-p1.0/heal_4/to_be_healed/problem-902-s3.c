#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

typedef struct {
    char *key;
    long value;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
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
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
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
        for (size_t index = 0U; index < dictionary->size; ++index) {
            free(dictionary->entries[index].key);
        }
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->size = 0U;
    dictionary->capacity = 0U;
}

static int dictionary_is_valid(const Dictionary *dictionary)
{
    if (dictionary == NULL ||
        dictionary->size > dictionary->capacity ||
        (dictionary->capacity != 0U && dictionary->entries == NULL)) {
        return 0;
    }

    return 1;
}

static int dictionary_reserve(Dictionary *dictionary, size_t capacity)
{
    Entry *resized_entries;

    if (!dictionary_is_valid(dictionary)) {
        return -1;
    }

    if (capacity <= dictionary->capacity) {
        return 0;
    }

    if (capacity > SIZE_MAX / sizeof(*dictionary->entries)) {
        return -1;
    }

    resized_entries = realloc(dictionary->entries,
                              capacity * sizeof(*dictionary->entries));
    if (resized_entries == NULL) {
        return -1;
    }

    dictionary->entries = resized_entries;
    dictionary->capacity = capacity;
    return 0;
}

static int dictionary_find(const Dictionary *dictionary,
                           const char *key,
                           size_t key_length,
                           size_t *index)
{
    if (!dictionary_is_valid(dictionary) || key == NULL || index == NULL) {
        return -1;
    }

    for (size_t current = 0U; current < dictionary->size; ++current) {
        const char *stored_key = dictionary->entries[current].key;
        size_t stored_length;

        if (stored_key == NULL) {
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        stored_length = strlen(stored_key);
        if (stored_length == key_length &&
            memcmp(stored_key, key, key_length) == 0) {
            *index = current;
            return 1;
        }
    }

    return 0;
}

static int dictionary_add(Dictionary *dictionary,
                          const char *key,
                          size_t key_length,
                          long value)
{
    size_t index;
    int found;
    char *key_copy;

    if (!dictionary_is_valid(dictionary) ||
        key == NULL ||
        key_length == SIZE_MAX ||
        memchr(key, '\0', key_length) != NULL) {
        return -1;
    }

    found = dictionary_find(dictionary, key, key_length, &index);
    if (found < 0) {
        return -1;
    }

    if (found == 1) {
        long current_value = dictionary->entries[index].value;

        if ((value > 0L && current_value > LONG_MAX - value) ||
            (value < 0L && current_value < LONG_MIN - value)) {
            return -1;
        }

        dictionary->entries[index].value = current_value + value;
        return 0;
    }

    key_copy = duplicate_string(key, key_length);
    if (key_copy == NULL) {
        return -1;
    }

    if (dictionary->size == dictionary->capacity) {
        size_t new_capacity;

        if (dictionary->capacity == 0U) {
            new_capacity = 4U;
        } else {
            if (dictionary->capacity > SIZE_MAX / 2U) {
                free(key_copy);
                return -1;
            }

            new_capacity = dictionary->capacity * 2U;
        }

        if (dictionary_reserve(dictionary, new_capacity) != 0) {
            free(key_copy);
            return -1;
        }
    }

    dictionary->entries[dictionary->size].key = key_copy;
    dictionary->entries[dictionary->size].value = value;
    ++dictionary->size;
    return 0;
}

static int dictionary_add_cstring(Dictionary *dictionary,
                                  const char *key,
                                  long value)
{
    if (key == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    return dictionary_add(dictionary, key, strlen(key), value);
}

static int dictionary_combine(const Dictionary *first,
                              const Dictionary *second,
                              Dictionary *result)
{
    Dictionary combined = {NULL, 0U, 0U};
    size_t maximum_size;

    if (!dictionary_is_valid(first) ||
        !dictionary_is_valid(second) ||
        result == NULL ||
        result == first ||
        result == second ||
        !dictionary_is_valid(result)) {
        return -1;
    }

    if (first->size > SIZE_MAX - second->size) {
        return -1;
    }

    maximum_size = first->size + second->size;

    if (maximum_size > 0U &&
        dictionary_reserve(&combined, maximum_size) != 0) {
        return -1;
    }

    for (size_t index = 0U; index < first->size; ++index) {
        const char *key = first->entries[index].key;

        if (key == NULL ||
            dictionary_add_cstring(&combined,
                                   key,
                                   first->entries[index].value) != 0) {
            dictionary_destroy(&combined);
            return -1;
        }
    }

    for (size_t index = 0U; index < second->size; ++index) {
        const char *key = second->entries[index].key;

        if (key == NULL ||
            dictionary_add_cstring(&combined,
                                   key,
                                   second->entries[index].value) != 0) {
            dictionary_destroy(&combined);
            return -1;
        }
    }

    dictionary_destroy(result);
    *result = combined;
    return 0;
}

static int dictionary_print(const Dictionary *dictionary)
{
    if (!dictionary_is_valid(dictionary)) {
        return -1;
    }

    for (size_t index = 0U; index < dictionary->size; ++index) {
        const Entry *entry = &dictionary->entries[index];

        if (entry->key == NULL ||
            printf("%s: %ld\n", entry->key, entry->value) < 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    Dictionary first = {NULL, 0U, 0U};
    Dictionary second = {NULL, 0U, 0U};
    Dictionary combined = {NULL, 0U, 0U};
    int status = EXIT_FAILURE;

    if (dictionary_add(&first, "apple", sizeof("apple") - 1U, 3L) != 0 ||
        dictionary_add(&first, "banana", sizeof("banana") - 1U, 5L) != 0 ||
        dictionary_add(&second, "banana", sizeof("banana") - 1U, 7L) != 0 ||
        dictionary_add(&second, "orange", sizeof("orange") - 1U, 4L) != 0) {
        goto cleanup;
    }

    if (dictionary_combine(&first, &second, &combined) != 0) {
        goto cleanup;
    }

    if (dictionary_print(&combined) != 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(&combined);
    dictionary_destroy(&second);
    dictionary_destroy(&first);
    return status;
}