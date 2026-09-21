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
    size_t capacity;
} Dictionary;

static char *duplicate_string(const char *source, size_t max_length)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || max_length == 0U) {
        return NULL;
    }

    terminator = memchr(source, '\0', max_length);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);
    if (length == SIZE_MAX) {
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

static int dictionary_init(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return 0;
    }

    dictionary->entries = NULL;
    dictionary->size = 0U;
    dictionary->capacity = 0U;
    return 1;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return;
    }

    for (index = 0U; index < dictionary->size; ++index) {
        free(dictionary->entries[index].key);
        free(dictionary->entries[index].value);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->size = 0U;
    dictionary->capacity = 0U;
}

static size_t dictionary_find(
    const Dictionary *dictionary,
    const char *key,
    size_t key_size)
{
    const char *terminator;
    size_t key_length;
    size_t index;

    if (dictionary == NULL || key == NULL || key_size == 0U) {
        return SIZE_MAX;
    }

    terminator = memchr(key, '\0', key_size);
    if (terminator == NULL) {
        return SIZE_MAX;
    }

    key_length = (size_t)(terminator - key);

    for (index = 0U; index < dictionary->size; ++index) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t stored_length = strlen(dictionary->entries[index].key);

        if (stored_length == key_length &&
            memcmp(dictionary->entries[index].key, key, key_length) == 0) {
            return index;
        }
    }

    return SIZE_MAX;
}

static int dictionary_reserve(Dictionary *dictionary, size_t capacity)
{
    DictionaryEntry *new_entries;

    if (dictionary == NULL) {
        return 0;
    }

    if (capacity <= dictionary->capacity) {
        return 1;
    }

    if (capacity > SIZE_MAX / sizeof(*new_entries)) {
        return 0;
    }

    new_entries = realloc(
        dictionary->entries,
        capacity * sizeof(*new_entries));

    if (new_entries == NULL) {
        return 0;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = capacity;
    return 1;
}

static int dictionary_set(
    Dictionary *dictionary,
    const char *key,
    size_t key_size,
    const char *value,
    size_t value_size)
{
    size_t index;
    char *new_key;
    char *new_value;

    if (dictionary == NULL || key == NULL || value == NULL ||
        key_size == 0U || value_size == 0U) {
        return 0;
    }

    if (memchr(key, '\0', key_size) == NULL ||
        memchr(value, '\0', value_size) == NULL) {
        return 0;
    }

    index = dictionary_find(dictionary, key, key_size);

    if (index != SIZE_MAX) {
        new_value = duplicate_string(value, value_size);
        if (new_value == NULL) {
            return 0;
        }

        free(dictionary->entries[index].value);
        dictionary->entries[index].value = new_value;
        return 1;
    }

    if (dictionary->size == dictionary->capacity) {
        size_t new_capacity;

        if (dictionary->capacity == 0U) {
            new_capacity = 4U;
        } else {
            if (dictionary->capacity > SIZE_MAX / 2U) {
                return 0;
            }

            new_capacity = dictionary->capacity * 2U;
        }

        if (!dictionary_reserve(dictionary, new_capacity)) {
            return 0;
        }
    }

    new_key = duplicate_string(key, key_size);
    if (new_key == NULL) {
        return 0;
    }

    new_value = duplicate_string(value, value_size);
    if (new_value == NULL) {
        free(new_key);
        return 0;
    }

    dictionary->entries[dictionary->size].key = new_key;
    dictionary->entries[dictionary->size].value = new_value;
    ++dictionary->size;

    return 1;
}

static int dictionary_merge(
    const Dictionary *first,
    const Dictionary *second,
    Dictionary *result)
{
    Dictionary temporary;
    size_t index;

    if (first == NULL || second == NULL || result == NULL ||
        result == first || result == second) {
        return 0;
    }

    if (!dictionary_init(&temporary)) {
        return 0;
    }

    if (first->size > SIZE_MAX - second->size) {
        return 0;
    }

    if (!dictionary_reserve(
            &temporary,
            first->size + second->size)) {
        dictionary_destroy(&temporary);
        return 0;
    }

    for (index = 0U; index < first->size; ++index) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t key_size = strlen(first->entries[index].key) + 1U;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t value_size = strlen(first->entries[index].value) + 1U;

        if (!dictionary_set(
                &temporary,
                first->entries[index].key,
                key_size,
                first->entries[index].value,
                value_size)) {
            dictionary_destroy(&temporary);
            return 0;
        }
    }

    for (index = 0U; index < second->size; ++index) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t key_size = strlen(second->entries[index].key) + 1U;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t value_size = strlen(second->entries[index].value) + 1U;

        if (!dictionary_set(
                &temporary,
                second->entries[index].key,
                key_size,
                second->entries[index].value,
                value_size)) {
            dictionary_destroy(&temporary);
            return 0;
        }
    }

    dictionary_destroy(result);
    *result = temporary;
    return 1;
}

static int dictionary_print(const Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return 0;
    }

    for (index = 0U; index < dictionary->size; ++index) {
        if (printf(
                "%s: %s\n",
                dictionary->entries[index].key,
                dictionary->entries[index].value) < 0) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    Dictionary first;
    Dictionary second;
    Dictionary merged;
    int exit_status = EXIT_FAILURE;

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

    if (!dictionary_set(
            &first, "name", sizeof("name"), "Alice", sizeof("Alice")) ||
        !dictionary_set(
            &first, "city", sizeof("city"), "London", sizeof("London")) ||
        !dictionary_set(
            &second, "city", sizeof("city"), "Paris", sizeof("Paris")) ||
        !dictionary_set(
            &second, "language", sizeof("language"), "C", sizeof("C"))) {
        goto cleanup;
    }

    if (!dictionary_merge(&first, &second, &merged)) {
        goto cleanup;
    }

    if (!dictionary_print(&merged)) {
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(&merged);
    dictionary_destroy(&second);
    dictionary_destroy(&first);

    return exit_status;
}