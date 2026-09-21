#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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

static char *duplicate_string_n(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length >= SIZE_MAX) {
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
        const Entry *entry = &dictionary->entries[index];

        if (entry->key != NULL &&
            entry->key_length == key_length &&
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
    size_t index;
    char *key_copy;
    char *value_copy;

    if (dictionary == NULL || key == NULL || value == NULL ||
        key_length >= SIZE_MAX || value_length >= SIZE_MAX) {
        return -1;
    }

    index = dictionary_find(dictionary, key, key_length);
    if (index != SIZE_MAX) {
        value_copy = duplicate_string_n(value, value_length);
        if (value_copy == NULL) {
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

        if (dictionary_reserve(dictionary, new_capacity) != 0) {
            return -1;
        }
    }

    key_copy = duplicate_string_n(key, key_length);
    if (key_copy == NULL) {
        return -1;
    }

    value_copy = duplicate_string_n(value, value_length);
    if (value_copy == NULL) {
        free(key_copy);
        return -1;
    }

    dictionary->entries[dictionary->count].key = key_copy;
    dictionary->entries[dictionary->count].key_length = key_length;
    dictionary->entries[dictionary->count].value = value_copy;
    dictionary->entries[dictionary->count].value_length = value_length;
    ++dictionary->count;

    return 0;
}

static int dictionary_merge_one(Dictionary *result,
                                const Dictionary *source)
{
    size_t index;

    if (result == NULL || source == NULL) {
        return -1;
    }

    for (index = 0U; index < source->count; ++index) {
        const Entry *entry = &source->entries[index];

        if (entry->key == NULL || entry->value == NULL ||
            dictionary_set_n(result,
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

    if (first == NULL || second == NULL || third == NULL ||
        result == NULL || result == first || result == second ||
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

static void print_quoted_bytes(const char *text, size_t length)
{
    putchar('"');

    if (text != NULL) {
        for (size_t index = 0U; index < length; ++index) {
            unsigned char ch = (unsigned char)text[index];

            switch (ch) {
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
                    if (ch < 0x20U) {
                        fprintf(stdout, "\\u%04x", (unsigned int)ch);
                    } else {
                        putchar((int)ch);
                    }
                    break;
            }
        }
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
        const Entry *entry = &dictionary->entries[index];

        if (index != 0U) {
            fputs(", ", stdout);
        }

        print_quoted_bytes(entry->key, entry->key_length);
        fputs(": ", stdout);
        print_quoted_bytes(entry->value, entry->value_length);
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