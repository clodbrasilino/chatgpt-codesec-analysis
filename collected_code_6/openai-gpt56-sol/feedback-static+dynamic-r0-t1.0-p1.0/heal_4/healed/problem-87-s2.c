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

    if (source_length > 0U) {
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

    if (dictionary->entries != NULL) {
        for (index = 0U; index < dictionary->count; ++index) {
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

    if (dictionary == NULL || key == NULL ||
        dictionary->count > dictionary->capacity ||
        (dictionary->count > 0U && dictionary->entries == NULL)) {
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
    char *key_copy = NULL;
    char *value_copy = NULL;

    if (dictionary == NULL || key == NULL || value == NULL ||
        key_length == SIZE_MAX || value_length == SIZE_MAX ||
        dictionary->count > dictionary->capacity ||
        (dictionary->count > 0U && dictionary->entries == NULL)) {
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

    if (dictionary->count == SIZE_MAX) {
        return -1;
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

    dictionary->entries[dictionary->count].key = key_copy;
    dictionary->entries[dictionary->count].key_length = key_length;
    dictionary->entries[dictionary->count].value = value_copy;
    dictionary->entries[dictionary->count].value_length = value_length;
    ++dictionary->count;

    return 0;
}

static int dictionary_set(Dictionary *dictionary,
                          const char *key,
                          const char *value)
{
    if (dictionary == NULL || key == NULL || value == NULL) {
        return -1;
    }

    return dictionary_set_n(dictionary,
                            key,
                            strlen(key),
                            value,
                            strlen(value));
}

static int dictionary_merge_one(Dictionary *result,
                                const Dictionary *source)
{
    size_t index;

    if (result == NULL || source == NULL ||
        source->count > source->capacity ||
        (source->count > 0U && source->entries == NULL)) {
        return -1;
    }

    for (index = 0U; index < source->count; ++index) {
        const Entry *entry = &source->entries[index];

        if (entry->key == NULL || entry->value == NULL ||
            entry->key_length == SIZE_MAX ||
            entry->value_length == SIZE_MAX) {
            return -1;
        }

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

    if (first == NULL || second == NULL || third == NULL || result == NULL ||
        result == first || result == second || result == third) {
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
    size_t index;

    if (text == NULL || putchar('"') == EOF) {
        return -1;
    }

    for (index = 0U; index < length; ++index) {
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
                        putchar(hex_digits[character >> 4U]) == EOF ||
                        putchar(hex_digits[character & 0x0FU]) == EOF) {
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
    size_t index;

    if (dictionary == NULL ||
        dictionary->count > dictionary->capacity ||
        (dictionary->count > 0U && dictionary->entries == NULL)) {
        return -1;
    }

    if (putchar('{') == EOF) {
        return -1;
    }

    for (index = 0U; index < dictionary->count; ++index) {
        const Entry *entry = &dictionary->entries[index];

        if (entry->key == NULL || entry->value == NULL) {
            return -1;
        }

        if (index > 0U && fputs(", ", stdout) == EOF) {
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