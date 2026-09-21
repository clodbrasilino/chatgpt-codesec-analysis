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
    size_t count;
    size_t capacity;
} Dictionary;

static int bounded_string_length(const char *string,
                                 size_t maximum_length,
                                 size_t *length)
{
    const char *terminator;

    if (string == NULL || length == NULL) {
        return 0;
    }

    terminator = memchr(string, '\0', maximum_length);
    if (terminator == NULL) {
        return 0;
    }

    *length = (size_t)(terminator - string);
    return 1;
}

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

    if (length != 0U) {
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
    size_t index;

    if (dictionary == NULL) {
        return;
    }

    for (index = 0U; index < dictionary->count; ++index) {
        free(dictionary->entries[index].key);
        free(dictionary->entries[index].value);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->count = 0U;
    dictionary->capacity = 0U;
}

static size_t dictionary_find(const Dictionary *dictionary,
                              const char *key,
                              size_t key_length)
{
    size_t index;

    if (dictionary == NULL || key == NULL) {
        return SIZE_MAX;
    }

    for (index = 0U; index < dictionary->count; ++index) {
        const char *stored_key = dictionary->entries[index].key;
        size_t stored_length;

        if (stored_key == NULL) {
            continue;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        stored_length = strlen(stored_key);
        if (stored_length == key_length &&
            (key_length == 0U ||
             memcmp(stored_key, key, key_length) == 0)) {
            return index;
        }
    }

    return SIZE_MAX;
}

static int dictionary_reserve(Dictionary *dictionary, size_t capacity)
{
    Entry *new_entries;

    if (dictionary == NULL) {
        return 0;
    }

    if (capacity <= dictionary->capacity) {
        return 1;
    }

    if (capacity > SIZE_MAX / sizeof(*dictionary->entries)) {
        return 0;
    }

    new_entries = realloc(dictionary->entries,
                          capacity * sizeof(*dictionary->entries));
    if (new_entries == NULL) {
        return 0;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = capacity;
    return 1;
}

static int dictionary_set(Dictionary *dictionary,
                          const char *key,
                          size_t key_length,
                          const char *value,
                          size_t value_length)
{
    size_t index;
    char *new_key;
    char *new_value;

    if (dictionary == NULL || key == NULL || value == NULL ||
        key_length == SIZE_MAX || value_length == SIZE_MAX) {
        return 0;
    }

    index = dictionary_find(dictionary, key, key_length);

    new_value = duplicate_string(value, value_length);
    if (new_value == NULL) {
        return 0;
    }

    if (index != SIZE_MAX) {
        free(dictionary->entries[index].value);
        dictionary->entries[index].value = new_value;
        return 1;
    }

    new_key = duplicate_string(key, key_length);
    if (new_key == NULL) {
        free(new_value);
        return 0;
    }

    if (dictionary->count == dictionary->capacity) {
        size_t new_capacity;

        if (dictionary->capacity == 0U) {
            new_capacity = 4U;
        } else {
            if (dictionary->capacity > SIZE_MAX / 2U) {
                free(new_key);
                free(new_value);
                return 0;
            }

            new_capacity = dictionary->capacity * 2U;
        }

        if (!dictionary_reserve(dictionary, new_capacity)) {
            free(new_key);
            free(new_value);
            return 0;
        }
    }

    dictionary->entries[dictionary->count].key = new_key;
    dictionary->entries[dictionary->count].value = new_value;
    ++dictionary->count;

    return 1;
}

static int dictionary_set_cstr(Dictionary *dictionary,
                               const char *key,
                               const char *value)
{
    size_t key_length;
    size_t value_length;

    if (!bounded_string_length(key, SIZE_MAX, &key_length) ||
        !bounded_string_length(value, SIZE_MAX, &value_length)) {
        return 0;
    }

    return dictionary_set(dictionary,
                          key,
                          key_length,
                          value,
                          value_length);
}

static int dictionary_merge(const Dictionary *first,
                            const Dictionary *second,
                            Dictionary *result)
{
    size_t index;
    Dictionary merged = { NULL, 0U, 0U };

    if (first == NULL || second == NULL || result == NULL ||
        first == result || second == result) {
        return 0;
    }

    if (first->count > SIZE_MAX - second->count) {
        return 0;
    }

    if (!dictionary_reserve(&merged, first->count + second->count)) {
        return 0;
    }

    for (index = 0U; index < first->count; ++index) {
        const Entry *entry = &first->entries[index];

        if (entry->key == NULL || entry->value == NULL ||
            !dictionary_set_cstr(&merged, entry->key, entry->value)) {
            dictionary_destroy(&merged);
            return 0;
        }
    }

    for (index = 0U; index < second->count; ++index) {
        const Entry *entry = &second->entries[index];

        if (entry->key == NULL || entry->value == NULL ||
            !dictionary_set_cstr(&merged, entry->key, entry->value)) {
            dictionary_destroy(&merged);
            return 0;
        }
    }

    dictionary_destroy(result);
    *result = merged;
    return 1;
}

static int dictionary_print(const Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return 0;
    }

    if (fputc('{', stdout) == EOF) {
        return 0;
    }

    for (index = 0U; index < dictionary->count; ++index) {
        const Entry *entry = &dictionary->entries[index];

        if (entry->key == NULL || entry->value == NULL) {
            return 0;
        }

        if (fprintf(stdout,
                    "%s\"%s\": \"%s\"",
                    index == 0U ? "" : ", ",
                    entry->key,
                    entry->value) < 0) {
            return 0;
        }
    }

    return fputs("}\n", stdout) != EOF;
}

int main(void)
{
    Dictionary first = { NULL, 0U, 0U };
    Dictionary second = { NULL, 0U, 0U };
    Dictionary merged = { NULL, 0U, 0U };
    int status = EXIT_FAILURE;

    if (!dictionary_set_cstr(&first, "name", "Alice") ||
        !dictionary_set_cstr(&first, "role", "developer") ||
        !dictionary_set_cstr(&second, "role", "lead developer") ||
        !dictionary_set_cstr(&second, "location", "London")) {
        goto cleanup;
    }

    if (!dictionary_merge(&first, &second, &merged)) {
        goto cleanup;
    }

    if (!dictionary_print(&merged)) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(&merged);
    dictionary_destroy(&second);
    dictionary_destroy(&first);
    return status;
}