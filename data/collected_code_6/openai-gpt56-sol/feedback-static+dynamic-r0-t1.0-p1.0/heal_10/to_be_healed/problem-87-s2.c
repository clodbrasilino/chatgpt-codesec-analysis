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
    size_t count;
    size_t capacity;
} Dictionary;

static int duplicate_string(const char *source, size_t source_length, char **result)
{
    char *copy;

    if (source == NULL || result == NULL || source_length == SIZE_MAX) {
        return -1;
    }

    *result = NULL;

    copy = malloc(source_length + 1U);
    if (copy == NULL) {
        return -1;
    }

    if (source_length != 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, source_length);
    }

    copy[source_length] = '\0';
    *result = copy;
    return 0;
}

static int dictionary_is_valid(const Dictionary *dictionary)
{
    if (dictionary == NULL ||
        dictionary->count > dictionary->capacity ||
        (dictionary->capacity == 0U && dictionary->entries != NULL) ||
        (dictionary->capacity != 0U && dictionary->entries == NULL)) {
        return 0;
    }

    for (size_t index = 0U; index < dictionary->count; ++index) {
        const Entry *entry = &dictionary->entries[index];

        if (entry->key == NULL ||
            entry->value == NULL ||
            entry->key_length == SIZE_MAX ||
            entry->value_length == SIZE_MAX) {
            return 0;
        }
    }

    return 1;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return;
    }

    if (dictionary->entries != NULL &&
        dictionary->count <= dictionary->capacity) {
        for (size_t index = 0U; index < dictionary->count; ++index) {
            free(dictionary->entries[index].key);
            free(dictionary->entries[index].value);
        }
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->count = 0U;
    dictionary->capacity = 0U;
}

static int dictionary_reserve(Dictionary *dictionary, size_t capacity)
{
    Entry *new_entries;

    if (!dictionary_is_valid(dictionary)) {
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
    if (!dictionary_is_valid(dictionary) || key == NULL) {
        return SIZE_MAX;
    }

    for (size_t index = 0U; index < dictionary->count; ++index) {
        const Entry *entry = &dictionary->entries[index];

        if (entry->key_length == key_length &&
            (key_length == 0U ||
             memcmp(entry->key, key, key_length) == 0)) {
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
    char *key_copy = NULL;
    char *value_copy = NULL;
    size_t index;

    if (!dictionary_is_valid(dictionary) ||
        key == NULL ||
        value == NULL ||
        key_length == SIZE_MAX ||
        value_length == SIZE_MAX) {
        return -1;
    }

    index = dictionary_find(dictionary, key, key_length);

    if (index != SIZE_MAX) {
        if (duplicate_string(value, value_length, &value_copy) != 0) {
            return -1;
        }

        free(dictionary->entries[index].value);
        dictionary->entries[index].value = value_copy;
        dictionary->entries[index].value_length = value_length;
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

        if (new_capacity <= dictionary->count ||
            dictionary_reserve(dictionary, new_capacity) != 0) {
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

    dictionary->entries[dictionary->count] = (Entry){
        .key = key_copy,
        .key_length = key_length,
        .value = value_copy,
        .value_length = value_length
    };
    ++dictionary->count;

    return 0;
}

static int dictionary_set(Dictionary *dictionary,
                          const char *key,
                          size_t key_capacity,
                          const char *value,
                          size_t value_capacity)
{
    const char *key_end;
    const char *value_end;
    size_t key_length;
    size_t value_length;

    if (!dictionary_is_valid(dictionary) ||
        key == NULL ||
        value == NULL ||
        key_capacity == 0U ||
        value_capacity == 0U) {
        return -1;
    }

    key_end = memchr(key, '\0', key_capacity);
    value_end = memchr(value, '\0', value_capacity);

    if (key_end == NULL || value_end == NULL) {
        return -1;
    }

    key_length = (size_t)(key_end - key);
    value_length = (size_t)(value_end - value);

    return dictionary_set_n(dictionary, key, key_length,
                            value, value_length);
}

static int dictionary_merge_one(Dictionary *result,
                                const Dictionary *source)
{
    if (!dictionary_is_valid(result) ||
        !dictionary_is_valid(source) ||
        result == source) {
        return -1;
    }

    for (size_t index = 0U; index < source->count; ++index) {
        const Entry *entry = &source->entries[index];

        if (dictionary_set_n(result,
                             entry->key,
                             entry->key_length,
                             entry->value,
                             entry->value_length) != 0) {
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

    if (!dictionary_is_valid(first) ||
        !dictionary_is_valid(second) ||
        !dictionary_is_valid(third) ||
        !dictionary_is_valid(result) ||
        result == first ||
        result == second ||
        result == third) {
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

static int print_quoted(const char *text, size_t length)
{
    static const char hex_digits[] = "0123456789abcdef";

    if (text == NULL || putchar('"') == EOF) {
        return -1;
    }

    for (size_t index = 0U; index < length; ++index) {
        unsigned char character = (unsigned char)text[index];

        switch (character) {
            case '"':
                if (fputs("\\\"", stdout) == EOF) {
                    return -1;
                }
                break;
            case '\\':
                if (fputs("\\\\", stdout) == EOF) {
                    return -1;
                }
                break;
            case '\b':
                if (fputs("\\b", stdout) == EOF) {
                    return -1;
                }
                break;
            case '\f':
                if (fputs("\\f", stdout) == EOF) {
                    return -1;
                }
                break;
            case '\n':
                if (fputs("\\n", stdout) == EOF) {
                    return -1;
                }
                break;
            case '\r':
                if (fputs("\\r", stdout) == EOF) {
                    return -1;
                }
                break;
            case '\t':
                if (fputs("\\t", stdout) == EOF) {
                    return -1;
                }
                break;
            default:
                if (character < 0x20U) {
                    if (fputs("\\u00", stdout) == EOF ||
                        putchar((int)hex_digits[character >> 4U]) == EOF ||
                        putchar((int)hex_digits[character & 0x0FU]) == EOF) {
                        return -1;
                    }
                } else if (putchar((int)character) == EOF) {
                    return -1;
                }
                break;
        }
    }

    return putchar('"') == EOF ? -1 : 0;
}

static int dictionary_print(const Dictionary *dictionary)
{
    if (!dictionary_is_valid(dictionary) || putchar('{') == EOF) {
        return -1;
    }

    for (size_t index = 0U; index < dictionary->count; ++index) {
        const Entry *entry = &dictionary->entries[index];

        if (index != 0U && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (print_quoted(entry->key, entry->key_length) != 0 ||
            fputs(": ", stdout) == EOF ||
            print_quoted(entry->value, entry->value_length) != 0) {
            return -1;
        }
    }

    return fputs("}\n", stdout) == EOF ? -1 : 0;
}

int main(void)
{
    Dictionary first = {0};
    Dictionary second = {0};
    Dictionary third = {0};
    Dictionary merged = {0};
    int status = EXIT_FAILURE;

    if (dictionary_set(&first, "name", sizeof("name"),
                       "Alice", sizeof("Alice")) != 0 ||
        dictionary_set(&first, "city", sizeof("city"),
                       "London", sizeof("London")) != 0 ||
        dictionary_set(&second, "age", sizeof("age"),
                       "30", sizeof("30")) != 0 ||
        dictionary_set(&second, "city", sizeof("city"),
                       "Paris", sizeof("Paris")) != 0 ||
        dictionary_set(&third, "country", sizeof("country"),
                       "France", sizeof("France")) != 0 ||
        dictionary_set(&third, "age", sizeof("age"),
                       "31", sizeof("31")) != 0) {
        fputs("Failed to create dictionaries.\n", stderr);
        goto cleanup;
    }

    if (merge_three_dictionaries(&first, &second, &third, &merged) != 0) {
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
    dictionary_destroy(&third);
    dictionary_destroy(&second);
    dictionary_destroy(&first);
    return status;
}