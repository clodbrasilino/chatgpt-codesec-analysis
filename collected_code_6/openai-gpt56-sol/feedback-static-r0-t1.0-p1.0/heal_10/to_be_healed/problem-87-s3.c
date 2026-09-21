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

    if (length != 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static int bounded_string_length(
    const char *string,
    size_t maximum_length,
    size_t *length)
{
    const char *terminator;

    if (string == NULL || length == NULL || maximum_length == 0U) {
        return 0;
    }

    terminator = memchr(string, '\0', maximum_length);
    if (terminator == NULL) {
        return 0;
    }

    *length = (size_t)(terminator - string);
    return 1;
}

static int dictionary_initialize(Dictionary *dictionary)
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
    if (dictionary == NULL) {
        return;
    }

    if (dictionary->entries != NULL) {
        for (size_t i = 0U; i < dictionary->size; ++i) {
            free(dictionary->entries[i].key);
            free(dictionary->entries[i].value);
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
        (dictionary->capacity == 0U && dictionary->entries != NULL) ||
        (dictionary->capacity != 0U && dictionary->entries == NULL)) {
        return 0;
    }

    for (size_t i = 0U; i < dictionary->size; ++i) {
        if (dictionary->entries[i].key == NULL ||
            dictionary->entries[i].value == NULL ||
            dictionary->entries[i].key_length == SIZE_MAX ||
            dictionary->entries[i].value_length == SIZE_MAX) {
            return 0;
        }
    }

    return 1;
}

static size_t dictionary_find(
    const Dictionary *dictionary,
    const char *key,
    size_t key_length)
{
    if (!dictionary_is_valid(dictionary) || key == NULL) {
        return SIZE_MAX;
    }

    for (size_t i = 0U; i < dictionary->size; ++i) {
        const Entry *entry = &dictionary->entries[i];

        if (entry->key_length == key_length &&
            (key_length == 0U ||
             memcmp(entry->key, key, key_length) == 0)) {
            return i;
        }
    }

    return SIZE_MAX;
}

static int dictionary_reserve(Dictionary *dictionary, size_t capacity)
{
    Entry *resized_entries;
    size_t old_capacity;

    if (!dictionary_is_valid(dictionary)) {
        return 0;
    }

    if (capacity <= dictionary->capacity) {
        return 1;
    }

    if (capacity > SIZE_MAX / sizeof(*dictionary->entries)) {
        return 0;
    }

    old_capacity = dictionary->capacity;
    resized_entries = realloc(
        dictionary->entries,
        capacity * sizeof(*dictionary->entries));

    if (resized_entries == NULL) {
        return 0;
    }

    memset(
        resized_entries + old_capacity,
        0,
        (capacity - old_capacity) * sizeof(*resized_entries));

    dictionary->entries = resized_entries;
    dictionary->capacity = capacity;
    return 1;
}

static int dictionary_set_n(
    Dictionary *dictionary,
    const char *key,
    size_t key_length,
    const char *value,
    size_t value_length)
{
    size_t index;
    char *key_copy;
    char *value_copy;

    if (!dictionary_is_valid(dictionary) ||
        key == NULL ||
        value == NULL ||
        key_length == SIZE_MAX ||
        value_length == SIZE_MAX) {
        return 0;
    }

    index = dictionary_find(dictionary, key, key_length);

    if (index != SIZE_MAX) {
        value_copy = duplicate_string(value, value_length);
        if (value_copy == NULL) {
            return 0;
        }

        free(dictionary->entries[index].value);
        dictionary->entries[index].value = value_copy;
        dictionary->entries[index].value_length = value_length;
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

    key_copy = duplicate_string(key, key_length);
    if (key_copy == NULL) {
        return 0;
    }

    value_copy = duplicate_string(value, value_length);
    if (value_copy == NULL) {
        free(key_copy);
        return 0;
    }

    dictionary->entries[dictionary->size] = (Entry){
        key_copy,
        key_length,
        value_copy,
        value_length
    };
    ++dictionary->size;

    return 1;
}

static int dictionary_set(
    Dictionary *dictionary,
    const char *key,
    size_t key_capacity,
    const char *value,
    size_t value_capacity)
{
    size_t key_length;
    size_t value_length;

    if (dictionary == NULL ||
        !bounded_string_length(key, key_capacity, &key_length) ||
        !bounded_string_length(value, value_capacity, &value_length)) {
        return 0;
    }

    return dictionary_set_n(
        dictionary,
        key,
        key_length,
        value,
        value_length);
}

static int dictionary_merge_one(
    Dictionary *destination,
    const Dictionary *source)
{
    if (!dictionary_is_valid(destination) ||
        !dictionary_is_valid(source) ||
        destination == source) {
        return 0;
    }

    for (size_t i = 0U; i < source->size; ++i) {
        const Entry *entry = &source->entries[i];

        if (!dictionary_set_n(
                destination,
                entry->key,
                entry->key_length,
                entry->value,
                entry->value_length)) {
            return 0;
        }
    }

    return 1;
}

static int merge_three_dictionaries(
    const Dictionary *first,
    const Dictionary *second,
    const Dictionary *third,
    Dictionary *result)
{
    Dictionary temporary = { NULL, 0U, 0U };

    if (!dictionary_is_valid(first) ||
        !dictionary_is_valid(second) ||
        !dictionary_is_valid(third) ||
        !dictionary_is_valid(result) ||
        result == first ||
        result == second ||
        result == third) {
        return 0;
    }

    if (!dictionary_merge_one(&temporary, first) ||
        !dictionary_merge_one(&temporary, second) ||
        !dictionary_merge_one(&temporary, third)) {
        dictionary_destroy(&temporary);
        return 0;
    }

    dictionary_destroy(result);
    *result = temporary;
    return 1;
}

static int print_quoted_string(const char *text, size_t length)
{
    if (text == NULL || putchar('"') == EOF) {
        return 0;
    }

    for (size_t i = 0U; i < length; ++i) {
        unsigned char current = (unsigned char)text[i];

        switch (current) {
            case '"':
                if (fputs("\\\"", stdout) == EOF) {
                    return 0;
                }
                break;
            case '\\':
                if (fputs("\\\\", stdout) == EOF) {
                    return 0;
                }
                break;
            case '\b':
                if (fputs("\\b", stdout) == EOF) {
                    return 0;
                }
                break;
            case '\f':
                if (fputs("\\f", stdout) == EOF) {
                    return 0;
                }
                break;
            case '\n':
                if (fputs("\\n", stdout) == EOF) {
                    return 0;
                }
                break;
            case '\r':
                if (fputs("\\r", stdout) == EOF) {
                    return 0;
                }
                break;
            case '\t':
                if (fputs("\\t", stdout) == EOF) {
                    return 0;
                }
                break;
            default:
                if (current < 0x20U) {
                    if (fprintf(stdout, "\\u%04x",
                                (unsigned int)current) < 0) {
                        return 0;
                    }
                } else if (current < 0x80U) {
                    if (putchar((int)current) == EOF) {
                        return 0;
                    }
                } else {
                    if (fprintf(stdout, "\\u00%02x",
                                (unsigned int)current) < 0) {
                        return 0;
                    }
                }
                break;
        }
    }

    return putchar('"') != EOF;
}

static int dictionary_print(const Dictionary *dictionary)
{
    if (!dictionary_is_valid(dictionary) || putchar('{') == EOF) {
        return 0;
    }

    for (size_t i = 0U; i < dictionary->size; ++i) {
        const Entry *entry = &dictionary->entries[i];

        if (i != 0U && fputs(", ", stdout) == EOF) {
            return 0;
        }

        if (!print_quoted_string(entry->key, entry->key_length) ||
            fputs(": ", stdout) == EOF ||
            !print_quoted_string(entry->value, entry->value_length)) {
            return 0;
        }
    }

    return puts("}") != EOF;
}

#define DICTIONARY_SET_LITERAL(dictionary, key, value) \
    dictionary_set(                                    \
        (dictionary),                                  \
        (key),                                         \
        sizeof(key),                                   \
        (value),                                       \
        sizeof(value))

int main(void)
{
    Dictionary first = { NULL, 0U, 0U };
    Dictionary second = { NULL, 0U, 0U };
    Dictionary third = { NULL, 0U, 0U };
    Dictionary merged = { NULL, 0U, 0U };
    int status = EXIT_FAILURE;

    if (!dictionary_initialize(&first) ||
        !dictionary_initialize(&second) ||
        !dictionary_initialize(&third) ||
        !dictionary_initialize(&merged)) {
        goto cleanup;
    }

    if (!DICTIONARY_SET_LITERAL(&first, "name", "Alice") ||
        !DICTIONARY_SET_LITERAL(&first, "city", "London") ||
        !DICTIONARY_SET_LITERAL(&second, "age", "30") ||
        !DICTIONARY_SET_LITERAL(&second, "city", "Paris") ||
        !DICTIONARY_SET_LITERAL(&third, "role", "Developer") ||
        !DICTIONARY_SET_LITERAL(&third, "name", "Bob")) {
        goto cleanup;
    }

    if (!merge_three_dictionaries(&first, &second, &third, &merged) ||
        !dictionary_print(&merged)) {
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