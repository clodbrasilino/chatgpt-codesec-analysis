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

static int duplicate_string(const char *source, size_t source_length, char **result)
{
    char *copy;

    if (source == NULL || result == NULL) {
        return -1;
    }

    *result = NULL;

    if (source_length == SIZE_MAX) {
        return -1;
    }

    copy = malloc(source_length + 1U);
    if (copy == NULL) {
        return -1;
    }

    if (source_length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, source_length);
    }

    copy[source_length] = '\0';
    *result = copy;
    return 0;
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

static size_t dictionary_find(const Dictionary *dictionary,
                              const char *key,
                              size_t key_length)
{
    size_t index;

    if (dictionary == NULL || key == NULL) {
        return SIZE_MAX;
    }

    for (index = 0U; index < dictionary->count; ++index) {
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

static int dictionary_set_n(Dictionary *dictionary,
                            const char *key,
                            size_t key_length,
                            const char *value,
                            size_t value_length)
{
    size_t index;
    char *key_copy = NULL;
    char *value_copy = NULL;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return -1;
    }

    if (key_length == SIZE_MAX || value_length == SIZE_MAX) {
        return -1;
    }

    index = dictionary_find(dictionary, key, key_length);
    if (index != SIZE_MAX) {
        if (duplicate_string(value, value_length, &value_copy) != 0) {
            return -1;
        }

        free(dictionary->entries[index].value);
        dictionary->entries[index].value = value_copy;
        return 0;
    }

    if (dictionary->count == dictionary->capacity) {
        size_t new_capacity;

        if (dictionary->capacity == 0U) {
            new_capacity = 4U;
        } else {
            if (dictionary->capacity > SIZE_MAX / 2U) {
                return -1;
            }
            new_capacity = dictionary->capacity * 2U;
        }

        if (dictionary_reserve(dictionary, new_capacity) != 0) {
            return -1;
        }
    }

    if (duplicate_string(key, key_length, &key_copy) != 0) {
        return -1;
    }

    if (duplicate_string(value, value_length, &value_copy) != 0) {
        free(key_copy);
        return -1;
    }

    dictionary->entries[dictionary->count].key = key_copy;
    dictionary->entries[dictionary->count].value = value_copy;
    ++dictionary->count;

    return 0;
}

static int dictionary_set(Dictionary *dictionary,
                          const char *key,
                          const char *value)
{
    if (key == NULL || value == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    return dictionary_set_n(dictionary, key, strlen(key), value, strlen(value));
}

static int dictionary_merge_one(Dictionary *result,
                                const Dictionary *source)
{
    size_t index;

    if (result == NULL || source == NULL) {
        return -1;
    }

    for (index = 0U; index < source->count; ++index) {
        const char *key = source->entries[index].key;
        const char *value = source->entries[index].value;

        if (key == NULL || value == NULL ||
            dictionary_set_n(result,
                             key,
                             /* Possible weaknesses found:
                              * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                              */
                             strlen(key),
                             value,
                             /* Possible weaknesses found:
                              * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                              */
                             strlen(value)) != 0) {
            return -1;
        }
    }

    return 0;
}

static int merge_three_dictionaries(const Dictionary *first,
                                    const Dictionary *second,
                                    const Dictionary *third,
                                    Dictionary *result)
{
    Dictionary merged = {0};

    if (first == NULL || second == NULL || third == NULL || result == NULL) {
        return -1;
    }

    if (result == first || result == second || result == third) {
        return -1;
    }

    if (dictionary_merge_one(&merged, first) != 0 ||
        dictionary_merge_one(&merged, second) != 0 ||
        dictionary_merge_one(&merged, third) != 0) {
        dictionary_destroy(&merged);
        return -1;
    }

    dictionary_destroy(result);
    *result = merged;
    return 0;
}

static void dictionary_print(const Dictionary *dictionary)
{
    size_t index;

    if (dictionary == NULL) {
        return;
    }

    putchar('{');

    for (index = 0U; index < dictionary->count; ++index) {
        if (index != 0U) {
            fputs(", ", stdout);
        }

        printf("\"%s\": \"%s\"",
               dictionary->entries[index].key,
               dictionary->entries[index].value);
    }

    puts("}");
}

int main(void)
{
    Dictionary first = {0};
    Dictionary second = {0};
    Dictionary third = {0};
    Dictionary merged = {0};
    int status = EXIT_FAILURE;

    if (dictionary_set(&first, "name", "Alice") != 0 ||
        dictionary_set(&first, "city", "London") != 0 ||
        dictionary_set(&second, "age", "30") != 0 ||
        dictionary_set(&second, "city", "Paris") != 0 ||
        dictionary_set(&third, "country", "France") != 0 ||
        dictionary_set(&third, "age", "31") != 0) {
        fputs("Failed to create dictionaries.\n", stderr);
        goto cleanup;
    }

    if (merge_three_dictionaries(&first, &second, &third, &merged) != 0) {
        fputs("Failed to merge dictionaries.\n", stderr);
        goto cleanup;
    }

    dictionary_print(&merged);
    status = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(&merged);
    dictionary_destroy(&third);
    dictionary_destroy(&second);
    dictionary_destroy(&first);

    return status;
}