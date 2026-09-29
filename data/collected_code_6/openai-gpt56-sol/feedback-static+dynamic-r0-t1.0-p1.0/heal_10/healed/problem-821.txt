#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
    size_t key_length;
    size_t value_length;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

static int bounded_string_length(const char *string, size_t max_length,
                                 size_t *length)
{
    const char *terminator;

    if (string == NULL || length == NULL) {
        return -1;
    }

    terminator = memchr(string, '\0', max_length);
    if (terminator == NULL) {
        return -1;
    }

    *length = (size_t)(terminator - string);
    return 0;
}

static char *duplicate_string_n(const char *source, size_t source_size,
                                size_t length)
{
    char *copy;

    if (source == NULL || length > source_size || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0U) {
        memmove(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
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

static int dictionary_initialize(Dictionary *dictionary, size_t capacity)
{
    if (dictionary == NULL) {
        return -1;
    }

    dictionary->entries = NULL;
    dictionary->size = 0U;
    dictionary->capacity = 0U;

    if (capacity == 0U) {
        return 0;
    }

    if (capacity > SIZE_MAX / sizeof(*dictionary->entries)) {
        return -1;
    }

    dictionary->entries = calloc(capacity, sizeof(*dictionary->entries));
    if (dictionary->entries == NULL) {
        return -1;
    }

    dictionary->capacity = capacity;
    return 0;
}

static int dictionary_reserve(Dictionary *dictionary, size_t capacity)
{
    Entry *new_entries;
    size_t old_capacity;

    if (dictionary == NULL ||
        dictionary->size > dictionary->capacity ||
        (dictionary->capacity != 0U && dictionary->entries == NULL)) {
        return -1;
    }

    if (capacity <= dictionary->capacity) {
        return 0;
    }

    if (capacity > SIZE_MAX / sizeof(*dictionary->entries)) {
        return -1;
    }

    old_capacity = dictionary->capacity;
    new_entries = realloc(dictionary->entries,
                          capacity * sizeof(*dictionary->entries));
    if (new_entries == NULL) {
        return -1;
    }

    memset(new_entries + old_capacity, 0,
           (capacity - old_capacity) * sizeof(*new_entries));

    dictionary->entries = new_entries;
    dictionary->capacity = capacity;
    return 0;
}

static size_t dictionary_find_n(const Dictionary *dictionary,
                                const char *key, size_t key_length)
{
    if (dictionary == NULL || key == NULL ||
        dictionary->size > dictionary->capacity ||
        (dictionary->size != 0U && dictionary->entries == NULL)) {
        return SIZE_MAX;
    }

    for (size_t i = 0U; i < dictionary->size; ++i) {
        const Entry *entry = &dictionary->entries[i];

        if (entry->key != NULL &&
            entry->key_length == key_length &&
            (key_length == 0U ||
             memcmp(entry->key, key, key_length) == 0)) {
            return i;
        }
    }

    return SIZE_MAX;
}

static int dictionary_set_lengths(Dictionary *dictionary,
                                  const char *key, size_t key_size,
                                  size_t key_length, const char *value,
                                  size_t value_size, size_t value_length)
{
    size_t index;
    char *key_copy;
    char *value_copy;

    if (dictionary == NULL || key == NULL || value == NULL ||
        key_length > key_size || value_length > value_size ||
        key_length == SIZE_MAX || value_length == SIZE_MAX ||
        dictionary->size > dictionary->capacity ||
        (dictionary->capacity != 0U && dictionary->entries == NULL)) {
        return -1;
    }

    index = dictionary_find_n(dictionary, key, key_length);

    if (index != SIZE_MAX) {
        value_copy = duplicate_string_n(value, value_size, value_length);
        if (value_copy == NULL) {
            return -1;
        }

        free(dictionary->entries[index].value);
        dictionary->entries[index].value = value_copy;
        dictionary->entries[index].value_length = value_length;
        return 0;
    }

    if (dictionary->size == dictionary->capacity) {
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

    key_copy = duplicate_string_n(key, key_size, key_length);
    if (key_copy == NULL) {
        return -1;
    }

    value_copy = duplicate_string_n(value, value_size, value_length);
    if (value_copy == NULL) {
        free(key_copy);
        return -1;
    }

    dictionary->entries[dictionary->size].key = key_copy;
    dictionary->entries[dictionary->size].value = value_copy;
    dictionary->entries[dictionary->size].key_length = key_length;
    dictionary->entries[dictionary->size].value_length = value_length;
    ++dictionary->size;

    return 0;
}

static int dictionary_set_n(Dictionary *dictionary, const char *key,
                            size_t key_size, const char *value,
                            size_t value_size)
{
    size_t key_length;
    size_t value_length;

    if (bounded_string_length(key, key_size, &key_length) != 0 ||
        bounded_string_length(value, value_size, &value_length) != 0) {
        return -1;
    }

    return dictionary_set_lengths(dictionary, key, key_size, key_length,
                                  value, value_size, value_length);
}

#define DICTIONARY_SET(dictionary, key, value) \
    dictionary_set_n((dictionary), (key), sizeof(key), (value), sizeof(value))

static int dictionary_merge(const Dictionary *first,
                            const Dictionary *second,
                            Dictionary *result)
{
    Dictionary temporary = { NULL, 0U, 0U };
    size_t initial_capacity;

    if (first == NULL || second == NULL || result == NULL ||
        result == first || result == second ||
        first->size > first->capacity ||
        second->size > second->capacity ||
        (first->capacity != 0U && first->entries == NULL) ||
        (second->capacity != 0U && second->entries == NULL) ||
        first->size > SIZE_MAX - second->size) {
        return -1;
    }

    initial_capacity = first->size + second->size;

    if (dictionary_initialize(&temporary, initial_capacity) != 0) {
        return -1;
    }

    for (size_t i = 0U; i < first->size; ++i) {
        const Entry *entry = &first->entries[i];

        if (entry->key == NULL || entry->value == NULL ||
            entry->key_length == SIZE_MAX ||
            entry->value_length == SIZE_MAX ||
            dictionary_set_lengths(&temporary,
                                   entry->key, entry->key_length,
                                   entry->key_length,
                                   entry->value, entry->value_length,
                                   entry->value_length) != 0) {
            dictionary_destroy(&temporary);
            return -1;
        }
    }

    for (size_t i = 0U; i < second->size; ++i) {
        const Entry *entry = &second->entries[i];

        if (entry->key == NULL || entry->value == NULL ||
            entry->key_length == SIZE_MAX ||
            entry->value_length == SIZE_MAX ||
            dictionary_set_lengths(&temporary,
                                   entry->key, entry->key_length,
                                   entry->key_length,
                                   entry->value, entry->value_length,
                                   entry->value_length) != 0) {
            dictionary_destroy(&temporary);
            return -1;
        }
    }

    dictionary_destroy(result);
    *result = temporary;
    return 0;
}

static int write_quoted_string(const char *string, size_t length)
{
    if (string == NULL || putchar('"') == EOF) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        unsigned char character = (unsigned char)string[i];

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
                if (fprintf(stdout, "\\u%04x",
                            (unsigned int)character) < 0) {
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
    if (dictionary == NULL ||
        dictionary->size > dictionary->capacity ||
        (dictionary->size != 0U && dictionary->entries == NULL)) {
        return -1;
    }

    if (putchar('{') == EOF) {
        return -1;
    }

    for (size_t i = 0U; i < dictionary->size; ++i) {
        const Entry *entry = &dictionary->entries[i];

        if (entry->key == NULL || entry->value == NULL) {
            return -1;
        }

        if (i != 0U && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (write_quoted_string(entry->key, entry->key_length) != 0 ||
            fputs(": ", stdout) == EOF ||
            write_quoted_string(entry->value, entry->value_length) != 0) {
            return -1;
        }
    }

    return puts("}") == EOF ? -1 : 0;
}

int main(void)
{
    Dictionary first = { NULL, 0U, 0U };
    Dictionary second = { NULL, 0U, 0U };
    Dictionary merged = { NULL, 0U, 0U };
    int status = EXIT_FAILURE;

    if (dictionary_initialize(&first, 0U) != 0 ||
        dictionary_initialize(&second, 0U) != 0) {
        goto cleanup;
    }

    if (DICTIONARY_SET(&first, "name", "Alice") != 0 ||
        DICTIONARY_SET(&first, "city", "Paris") != 0 ||
        DICTIONARY_SET(&second, "city", "London") != 0 ||
        DICTIONARY_SET(&second, "age", "30") != 0) {
        goto cleanup;
    }

    if (dictionary_merge(&first, &second, &merged) != 0) {
        goto cleanup;
    }

    if (dictionary_print(&merged) == 0) {
        status = EXIT_SUCCESS;
    }

cleanup:
    dictionary_destroy(&merged);
    dictionary_destroy(&second);
    dictionary_destroy(&first);
    return status;
}