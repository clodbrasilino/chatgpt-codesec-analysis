#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *key;
    char *value;
} Entry;

typedef struct {
    Entry *entries;
    size_t count;
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

    if (capacity > SIZE_MAX / sizeof(*new_entries)) {
        return -1;
    }

    new_entries = realloc(dictionary->entries,
                          capacity * sizeof(*new_entries));
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
        const char *stored_key = dictionary->entries[index].key;

        if (stored_key != NULL &&
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            strlen(stored_key) == key_length &&
            memcmp(stored_key, key, key_length) == 0) {
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
    char *key_copy;
    char *value_copy;

    if (dictionary == NULL || key == NULL || value == NULL ||
        key_length == SIZE_MAX || value_length == SIZE_MAX) {
        return -1;
    }

    index = dictionary_find(dictionary, key, key_length);
    if (index != SIZE_MAX) {
        value_copy = duplicate_string(value, value_length);
        if (value_copy == NULL) {
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

    key_copy = duplicate_string(key, key_length);
    if (key_copy == NULL) {
        return -1;
    }

    value_copy = duplicate_string(value, value_length);
    if (value_copy == NULL) {
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
    size_t key_length;
    size_t value_length;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    key_length = strlen(key);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    value_length = strlen(value);

    return dictionary_set_n(dictionary,
                            key,
                            key_length,
                            value,
                            value_length);
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
            dictionary_set(result, key, value) != 0) {
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

    if (first == NULL || second == NULL ||
        third == NULL || result == NULL) {
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

static void print_quoted_string(const char *text)
{
    const unsigned char *current =
        (const unsigned char *)(text != NULL ? text : "");

    putchar('"');

    while (*current != '\0') {
        switch (*current) {
            case '"':
                fputs("\\\"", stdout);
                break;
            case '\\':
                fputs("\\\\", stdout);
                break;
            case '\b':
                fputs("\\b", stdout);
                break;
            case '\f':
                fputs("\\f", stdout);
                break;
            case '\n':
                fputs("\\n", stdout);
                break;
            case '\r':
                fputs("\\r", stdout);
                break;
            case '\t':
                fputs("\\t", stdout);
                break;
            default:
                if (*current < 0x20U) {
                    printf("\\u%04x", (unsigned int)*current);
                } else {
                    putchar((int)*current);
                }
                break;
        }

        ++current;
    }

    putchar('"');
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

        print_quoted_string(dictionary->entries[index].key);
        fputs(": ", stdout);
        print_quoted_string(dictionary->entries[index].value);
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

    if (dictionary_set_n(&first, "name", sizeof("name") - 1U,
                         "Alice", sizeof("Alice") - 1U) != 0 ||
        dictionary_set_n(&first, "city", sizeof("city") - 1U,
                         "London", sizeof("London") - 1U) != 0 ||
        dictionary_set_n(&second, "age", sizeof("age") - 1U,
                         "30", sizeof("30") - 1U) != 0 ||
        dictionary_set_n(&second, "city", sizeof("city") - 1U,
                         "Paris", sizeof("Paris") - 1U) != 0 ||
        dictionary_set_n(&third, "country", sizeof("country") - 1U,
                         "France", sizeof("France") - 1U) != 0 ||
        dictionary_set_n(&third, "age", sizeof("age") - 1U,
                         "31", sizeof("31") - 1U) != 0) {
        fputs("Failed to create dictionaries.\n", stderr);
        goto cleanup;
    }

    if (merge_three_dictionaries(&first,
                                 &second,
                                 &third,
                                 &merged) != 0) {
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