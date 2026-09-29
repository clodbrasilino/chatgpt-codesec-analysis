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
    size_t size;
    size_t capacity;
} Dictionary;

static char *duplicate_string(const char *source, size_t max_length)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    terminator = memchr(source, '\0', max_length);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);

    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0U) {
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

    if (dictionary == NULL) {
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

static size_t dictionary_find(const Dictionary *dictionary,
                              const char *key,
                              size_t key_max_length)
{
    const char *key_terminator;
    size_t key_length;
    size_t i;

    if (dictionary == NULL || key == NULL) {
        return SIZE_MAX;
    }

    key_terminator = memchr(key, '\0', key_max_length);
    if (key_terminator == NULL) {
        return SIZE_MAX;
    }

    key_length = (size_t)(key_terminator - key);

    for (i = 0U; i < dictionary->size; ++i) {
        size_t stored_length;

        if (dictionary->entries[i].key == NULL) {
            continue;
        }

        stored_length = strlen(dictionary->entries[i].key);
        if (stored_length == key_length &&
            memcmp(dictionary->entries[i].key, key, key_length) == 0) {
            return i;
        }
    }

    return SIZE_MAX;
}

static int dictionary_set_n(Dictionary *dictionary,
                            const char *key,
                            size_t key_max_length,
                            const char *value,
                            size_t value_max_length)
{
    size_t index;
    size_t new_capacity;
    char *key_copy;
    char *value_copy;

    if (dictionary == NULL || key == NULL || value == NULL) {
        return -1;
    }

    if (memchr(key, '\0', key_max_length) == NULL ||
        memchr(value, '\0', value_max_length) == NULL) {
        return -1;
    }

    index = dictionary_find(dictionary, key, key_max_length);

    if (index != SIZE_MAX) {
        value_copy = duplicate_string(value, value_max_length);
        if (value_copy == NULL) {
            return -1;
        }

        free(dictionary->entries[index].value);
        dictionary->entries[index].value = value_copy;
        return 0;
    }

    if (dictionary->size == dictionary->capacity) {
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

    key_copy = duplicate_string(key, key_max_length);
    if (key_copy == NULL) {
        return -1;
    }

    value_copy = duplicate_string(value, value_max_length);
    if (value_copy == NULL) {
        free(key_copy);
        return -1;
    }

    dictionary->entries[dictionary->size].key = key_copy;
    dictionary->entries[dictionary->size].value = value_copy;
    ++dictionary->size;

    return 0;
}

#define DICTIONARY_SET(dictionary, key, value) \
    dictionary_set_n((dictionary), (key), sizeof(key), (value), sizeof(value))

static int dictionary_merge(const Dictionary *first,
                            const Dictionary *second,
                            Dictionary *result)
{
    Dictionary temporary = { NULL, 0U, 0U };
    size_t initial_capacity;
    size_t i;

    if (first == NULL || second == NULL || result == NULL ||
        result == first || result == second) {
        return -1;
    }

    if (first->size > SIZE_MAX - second->size) {
        return -1;
    }

    initial_capacity = first->size + second->size;

    if (dictionary_initialize(&temporary, initial_capacity) != 0) {
        return -1;
    }

    for (i = 0U; i < first->size; ++i) {
        size_t key_length;
        size_t value_length;

        if (first->entries[i].key == NULL ||
            first->entries[i].value == NULL) {
            dictionary_destroy(&temporary);
            return -1;
        }

        key_length = strlen(first->entries[i].key);
        value_length = strlen(first->entries[i].value);

        if (key_length == SIZE_MAX || value_length == SIZE_MAX ||
            dictionary_set_n(&temporary,
                             first->entries[i].key,
                             key_length + 1U,
                             first->entries[i].value,
                             value_length + 1U) != 0) {
            dictionary_destroy(&temporary);
            return -1;
        }
    }

    for (i = 0U; i < second->size; ++i) {
        size_t key_length;
        size_t value_length;

        if (second->entries[i].key == NULL ||
            second->entries[i].value == NULL) {
            dictionary_destroy(&temporary);
            return -1;
        }

        key_length = strlen(second->entries[i].key);
        value_length = strlen(second->entries[i].value);

        if (key_length == SIZE_MAX || value_length == SIZE_MAX ||
            dictionary_set_n(&temporary,
                             second->entries[i].key,
                             key_length + 1U,
                             second->entries[i].value,
                             value_length + 1U) != 0) {
            dictionary_destroy(&temporary);
            return -1;
        }
    }

    dictionary_destroy(result);
    *result = temporary;
    return 0;
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
        if (dictionary->entries[i].key == NULL ||
            dictionary->entries[i].value == NULL) {
            return -1;
        }

        if (i != 0U && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (printf("\"%s\": \"%s\"",
                   dictionary->entries[i].key,
                   dictionary->entries[i].value) < 0) {
            return -1;
        }
    }

    if (puts("}") == EOF) {
        return -1;
    }

    return 0;
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