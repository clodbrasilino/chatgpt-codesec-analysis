#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    size_t key_length;
    char *value;
    size_t value_length;
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

static char *duplicate_text(const char *source, size_t source_length)
{
    char *copy;
    size_t i;

    if (source == NULL) {
        errno = EINVAL;
        return NULL;
    }

    if (source_length == SIZE_MAX) {
        errno = EOVERFLOW;
        return NULL;
    }

    copy = malloc(source_length + 1);
    if (copy == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    for (i = 0; i < source_length; ++i) {
        if (source[i] == '\0') {
            free(copy);
            errno = EINVAL;
            return NULL;
        }

        copy[i] = source[i];
    }

    copy[source_length] = '\0';
    return copy;
}

static int text_equal(const char *left,
                      size_t left_length,
                      const char *right,
                      size_t right_length)
{
    size_t i;

    if (left_length != right_length) {
        return 0;
    }

    for (i = 0; i < left_length; ++i) {
        if (left[i] != right[i]) {
            return 0;
        }
    }

    return 1;
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

    new_entries = realloc(
        dictionary->entries,
        new_capacity * sizeof(*dictionary->entries));

    if (new_entries == NULL) {
        errno = ENOMEM;
        return -1;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = new_capacity;
    return 0;
}

static int dictionary_set(Dictionary *dictionary,
                          const char *key,
                          size_t key_length,
                          const char *value,
                          size_t value_length)
{
    size_t i;
    char *new_key;
    char *new_value;

    if (dictionary == NULL || key == NULL || value == NULL) {
        errno = EINVAL;
        return -1;
    }

    for (i = 0; i < dictionary->count; ++i) {
        if (text_equal(dictionary->entries[i].key,
                       dictionary->entries[i].key_length,
                       key,
                       key_length)) {
            new_value = duplicate_text(value, value_length);
            if (new_value == NULL) {
                return -1;
            }

            free(dictionary->entries[i].value);
            dictionary->entries[i].value = new_value;
            dictionary->entries[i].value_length = value_length;
            return 0;
        }
    }

    if (dictionary->count == SIZE_MAX) {
        errno = EOVERFLOW;
        return -1;
    }

    new_key = duplicate_text(key, key_length);
    if (new_key == NULL) {
        return -1;
    }

    new_value = duplicate_text(value, value_length);
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
    dictionary->entries[dictionary->count].key_length = key_length;
    dictionary->entries[dictionary->count].value = new_value;
    dictionary->entries[dictionary->count].value_length = value_length;
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
        if (dictionary_set(
                &merged,
                first->entries[i].key,
                first->entries[i].key_length,
                first->entries[i].value,
                first->entries[i].value_length) != 0) {
            dictionary_destroy(&merged);
            return -1;
        }
    }

    for (i = 0; i < second->count; ++i) {
        if (dictionary_set(
                &merged,
                second->entries[i].key,
                second->entries[i].key_length,
                second->entries[i].value,
                second->entries[i].value_length) != 0) {
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

    if (dictionary_set(
            &first,
            "name", sizeof("name") - 1,
            "Alice", sizeof("Alice") - 1) != 0 ||
        dictionary_set(
            &first,
            "city", sizeof("city") - 1,
            "London", sizeof("London") - 1) != 0 ||
        dictionary_set(
            &second,
            "city", sizeof("city") - 1,
            "Paris", sizeof("Paris") - 1) != 0 ||
        dictionary_set(
            &second,
            "language", sizeof("language") - 1,
            "C", sizeof("C") - 1) != 0) {
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