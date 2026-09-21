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
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0U; i < dictionary->size; ++i) {
        free(dictionary->entries[i].key);
        free(dictionary->entries[i].value);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->size = 0U;
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
    size_t i;

    if (dictionary == NULL || key == NULL) {
        return SIZE_MAX;
    }

    for (i = 0U; i < dictionary->size; ++i) {
        const Entry *entry = &dictionary->entries[i];

        if (entry->key_length == key_length &&
            (key_length == 0U ||
             memcmp(entry->key, key, key_length) == 0)) {
            return i;
        }
    }

    return SIZE_MAX;
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
        return -1;
    }

    index = dictionary_find(dictionary, key, key_length);

    new_value = duplicate_string(value, value_length);
    if (new_value == NULL) {
        return -1;
    }

    if (index != SIZE_MAX) {
        char *old_value = dictionary->entries[index].value;

        dictionary->entries[index].value = new_value;
        dictionary->entries[index].value_length = value_length;
        free(old_value);
        return 0;
    }

    new_key = duplicate_string(key, key_length);
    if (new_key == NULL) {
        free(new_value);
        return -1;
    }

    if (dictionary->size == dictionary->capacity) {
        size_t new_capacity;

        if (dictionary->capacity == 0U) {
            new_capacity = 4U;
        } else {
            if (dictionary->capacity > SIZE_MAX / 2U) {
                free(new_key);
                free(new_value);
                return -1;
            }

            new_capacity = dictionary->capacity * 2U;
        }

        if (dictionary_reserve(dictionary, new_capacity) != 0) {
            free(new_key);
            free(new_value);
            return -1;
        }
    }

    dictionary->entries[dictionary->size].key = new_key;
    dictionary->entries[dictionary->size].key_length = key_length;
    dictionary->entries[dictionary->size].value = new_value;
    dictionary->entries[dictionary->size].value_length = value_length;
    ++dictionary->size;

    return 0;
}

static int dictionary_set_string(Dictionary *dictionary,
                                 const char *key,
                                 size_t key_capacity,
                                 const char *value,
                                 size_t value_capacity)
{
    const char *key_end;
    const char *value_end;
    size_t key_length;
    size_t value_length;

    if (dictionary == NULL || key == NULL || value == NULL ||
        key_capacity == 0U || value_capacity == 0U) {
        return -1;
    }

    key_end = memchr(key, '\0', key_capacity);
    value_end = memchr(value, '\0', value_capacity);

    if (key_end == NULL || value_end == NULL) {
        return -1;
    }

    key_length = (size_t)(key_end - key);
    value_length = (size_t)(value_end - value);

    return dictionary_set(dictionary, key, key_length,
                          value, value_length);
}

static int dictionary_merge(const Dictionary *first,
                            const Dictionary *second,
                            Dictionary *result)
{
    Dictionary merged = {0};
    size_t required_capacity;
    size_t i;

    if (first == NULL || second == NULL || result == NULL ||
        result == first || result == second) {
        return -1;
    }

    if (first->size > SIZE_MAX - second->size) {
        return -1;
    }

    required_capacity = first->size + second->size;

    if (dictionary_reserve(&merged, required_capacity) != 0) {
        return -1;
    }

    for (i = 0U; i < first->size; ++i) {
        const Entry *entry = &first->entries[i];

        if (dictionary_set(&merged,
                           entry->key,
                           entry->key_length,
                           entry->value,
                           entry->value_length) != 0) {
            dictionary_destroy(&merged);
            return -1;
        }
    }

    for (i = 0U; i < second->size; ++i) {
        const Entry *entry = &second->entries[i];

        if (dictionary_set(&merged,
                           entry->key,
                           entry->key_length,
                           entry->value,
                           entry->value_length) != 0) {
            dictionary_destroy(&merged);
            return -1;
        }
    }

    dictionary_destroy(result);
    *result = merged;
    return 0;
}

static int write_quoted(const char *text, size_t length)
{
    size_t i;

    if (text == NULL || putchar('"') == EOF) {
        return -1;
    }

    for (i = 0U; i < length; ++i) {
        unsigned char c = (unsigned char)text[i];

        switch (c) {
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
            if (c < 0x20U) {
                if (fprintf(stdout, "\\u%04x", (unsigned int)c) < 0) {
                    return -1;
                }
            } else if (putchar((int)c) == EOF) {
                return -1;
            }
            break;
        }
    }

    return putchar('"') == EOF ? -1 : 0;
}

static int dictionary_print(const Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return -1;
    }

    if (putchar('{') == EOF) {
        return -1;
    }

    for (i = 0U; i < dictionary->size; ++i) {
        const Entry *entry = &dictionary->entries[i];

        if (i != 0U && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (write_quoted(entry->key, entry->key_length) != 0 ||
            fputs(": ", stdout) == EOF ||
            write_quoted(entry->value, entry->value_length) != 0) {
            return -1;
        }
    }

    return puts("}") == EOF ? -1 : 0;
}

int main(void)
{
    Dictionary first = {0};
    Dictionary second = {0};
    Dictionary merged = {0};
    int status = EXIT_FAILURE;

    if (dictionary_set_string(&first,
                              "name", sizeof("name"),
                              "Alice", sizeof("Alice")) != 0 ||
        dictionary_set_string(&first,
                              "city", sizeof("city"),
                              "London", sizeof("London")) != 0 ||
        dictionary_set_string(&second,
                              "city", sizeof("city"),
                              "Paris", sizeof("Paris")) != 0 ||
        dictionary_set_string(&second,
                              "role", sizeof("role"),
                              "Developer", sizeof("Developer")) != 0) {
        fputs("Failed to create dictionaries.\n", stderr);
        goto cleanup;
    }

    if (dictionary_merge(&first, &second, &merged) != 0) {
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
    dictionary_destroy(&second);
    dictionary_destroy(&first);
    return status;
}