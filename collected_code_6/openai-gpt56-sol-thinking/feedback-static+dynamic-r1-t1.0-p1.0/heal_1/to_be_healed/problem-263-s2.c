#include <errno.h>
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
    size_t count;
    size_t capacity;
} Dictionary;

static void dictionary_init(Dictionary *dictionary)
{
    if (dictionary != NULL) {
        dictionary->entries = NULL;
        dictionary->count = 0;
        dictionary->capacity = 0;
    }
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0; i < dictionary->count; ++i) {
        free(dictionary->entries[i].key);
        free(dictionary->entries[i].value);
    }

    free(dictionary->entries);
    dictionary_init(dictionary);
}

static char *duplicate_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        errno = EINVAL;
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(source);
    if (length == SIZE_MAX) {
        errno = EOVERFLOW;
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, source, length + 1);
    return copy;
}

static int dictionary_reserve(Dictionary *dictionary, size_t minimum_capacity)
{
    size_t new_capacity;
    DictionaryEntry *new_entries;

    if (dictionary == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (minimum_capacity <= dictionary->capacity) {
        return 0;
    }

    if (minimum_capacity > SIZE_MAX / sizeof(*dictionary->entries)) {
        errno = EOVERFLOW;
        return -1;
    }

    new_capacity = dictionary->capacity == 0 ? 8 : dictionary->capacity;

    while (new_capacity < minimum_capacity) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = minimum_capacity;
            break;
        }
        new_capacity *= 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*dictionary->entries)) {
        errno = EOVERFLOW;
        return -1;
    }

    new_entries = realloc(dictionary->entries,
                          new_capacity * sizeof(*dictionary->entries));
    if (new_entries == NULL) {
        return -1;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = new_capacity;
    return 0;
}

static int dictionary_set(Dictionary *dictionary,
                          const char *key,
                          const char *value)
{
    size_t i;
    char *new_key;
    char *new_value;

    if (dictionary == NULL || key == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    for (i = 0; i < dictionary->count; ++i) {
        if (strcmp(dictionary->entries[i].key, key) == 0) {
            new_value = duplicate_string(value);
            if (new_value == NULL) {
                return -1;
            }

            free(dictionary->entries[i].value);
            dictionary->entries[i].value = new_value;
            return 0;
        }
    }

    if (dictionary->count == SIZE_MAX) {
        errno = EOVERFLOW;
        return -1;
    }

    new_key = duplicate_string(key);
    if (new_key == NULL) {
        return -1;
    }

    new_value = duplicate_string(value);
    if (new_value == NULL) {
        free(new_key);
        return -1;
    }

    if (dictionary_reserve(dictionary, dictionary->count + 1) != 0) {
        free(new_key);
        free(new_value);
        return -1;
    }

    dictionary->entries[dictionary->count].key = new_key;
    dictionary->entries[dictionary->count].value = new_value;
    ++dictionary->count;

    return 0;
}

static int merge_dictionaries(const Dictionary *first,
                              const Dictionary *second,
                              Dictionary *result)
{
    Dictionary merged;
    size_t i;

    if (first == NULL || second == NULL || result == NULL) {
        errno = EINVAL;
        return -1;
    }

    dictionary_init(&merged);

    for (i = 0; i < first->count; ++i) {
        if (dictionary_set(&merged,
                           first->entries[i].key,
                           first->entries[i].value) != 0) {
            dictionary_destroy(&merged);
            return -1;
        }
    }

    for (i = 0; i < second->count; ++i) {
        if (dictionary_set(&merged,
                           second->entries[i].key,
                           second->entries[i].value) != 0) {
            dictionary_destroy(&merged);
            return -1;
        }
    }

    dictionary_destroy(result);
    *result = merged;
    return 0;
}

static void report_error(const char *operation)
{
    int error_number = errno;

    fprintf(stderr, "%s: %s\n", operation, strerror(error_number));
}

int main(void)
{
    Dictionary first;
    Dictionary second;
    Dictionary merged;
    size_t i;
    int exit_status = EXIT_FAILURE;

    dictionary_init(&first);
    dictionary_init(&second);
    dictionary_init(&merged);

    if (dictionary_set(&first, "name", "Alice") != 0 ||
        dictionary_set(&first, "city", "London") != 0 ||
        dictionary_set(&second, "city", "Paris") != 0 ||
        dictionary_set(&second, "language", "C") != 0) {
        report_error("Unable to create dictionaries");
        goto cleanup;
    }

    if (merge_dictionaries(&first, &second, &merged) != 0) {
        report_error("Unable to merge dictionaries");
        goto cleanup;
    }

    for (i = 0; i < merged.count; ++i) {
        if (printf("%s: %s\n",
                   merged.entries[i].key,
                   merged.entries[i].value) < 0) {
            report_error("Unable to write output");
            goto cleanup;
        }
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(&merged);
    dictionary_destroy(&second);
    dictionary_destroy(&first);
    return exit_status;
}