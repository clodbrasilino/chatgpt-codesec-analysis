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

static void dictionary_init(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return;
    }

    dictionary->entries = NULL;
    dictionary->size = 0;
    dictionary->capacity = 0;
}

static void dictionary_destroy(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0; i < dictionary->size; ++i) {
        free(dictionary->entries[i].key);
        free(dictionary->entries[i].value);
    }

    free(dictionary->entries);
    dictionary_init(dictionary);
}

static char *duplicate_string_n(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
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
    size_t i;

    if (dictionary == NULL || key == NULL) {
        return SIZE_MAX;
    }

    for (i = 0; i < dictionary->size; ++i) {
        const Entry *entry = &dictionary->entries[i];

        if (entry->key_length == key_length &&
            (key_length == 0 ||
             memcmp(entry->key, key, key_length) == 0)) {
            return i;
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
    char *value_copy;

    if (dictionary == NULL || key == NULL || value == NULL ||
        key_length == SIZE_MAX || value_length == SIZE_MAX) {
        return -1;
    }

    index = dictionary_find(dictionary, key, key_length);

    value_copy = duplicate_string_n(value, value_length);
    if (value_copy == NULL) {
        return -1;
    }

    if (index != SIZE_MAX) {
        free(dictionary->entries[index].value);
        dictionary->entries[index].value = value_copy;
        dictionary->entries[index].value_length = value_length;
        return 0;
    }

    {
        char *key_copy = duplicate_string_n(key, key_length);

        if (key_copy == NULL) {
            free(value_copy);
            return -1;
        }

        if (dictionary->size == dictionary->capacity) {
            size_t new_capacity;

            if (dictionary->capacity == 0) {
                new_capacity = 4;
            } else {
                if (dictionary->capacity > SIZE_MAX / 2) {
                    free(key_copy);
                    free(value_copy);
                    return -1;
                }

                new_capacity = dictionary->capacity * 2;
            }

            if (new_capacity <= dictionary->size ||
                dictionary_reserve(dictionary, new_capacity) != 0) {
                free(key_copy);
                free(value_copy);
                return -1;
            }
        }

        dictionary->entries[dictionary->size].key = key_copy;
        dictionary->entries[dictionary->size].key_length = key_length;
        dictionary->entries[dictionary->size].value = value_copy;
        dictionary->entries[dictionary->size].value_length = value_length;
        ++dictionary->size;
    }

    return 0;
}

static int dictionary_copy(Dictionary *destination,
                           const Dictionary *source)
{
    Dictionary copy;
    size_t i;

    if (destination == NULL || source == NULL || destination == source) {
        return -1;
    }

    dictionary_init(&copy);

    if (dictionary_reserve(&copy, source->size) != 0) {
        return -1;
    }

    for (i = 0; i < source->size; ++i) {
        const Entry *entry = &source->entries[i];

        if (dictionary_set_n(&copy,
                             entry->key,
                             entry->key_length,
                             entry->value,
                             entry->value_length) != 0) {
            dictionary_destroy(&copy);
            return -1;
        }
    }

    dictionary_destroy(destination);
    *destination = copy;
    return 0;
}

static int dictionary_merge(Dictionary *result,
                            const Dictionary *first,
                            const Dictionary *second)
{
    Dictionary merged;
    size_t i;

    if (result == NULL || first == NULL || second == NULL ||
        result == first || result == second) {
        return -1;
    }

    dictionary_init(&merged);

    if (dictionary_copy(&merged, first) != 0) {
        return -1;
    }

    for (i = 0; i < second->size; ++i) {
        const Entry *entry = &second->entries[i];

        if (dictionary_set_n(&merged,
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

static int print_bytes(const char *data, size_t length)
{
    if (data == NULL && length != 0) {
        return -1;
    }

    while (length != 0) {
        size_t written = fwrite(data, 1, length, stdout);

        if (written == 0) {
            return -1;
        }

        data += written;
        length -= written;
    }

    return 0;
}

static int dictionary_print(const Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return -1;
    }

    for (i = 0; i < dictionary->size; ++i) {
        const Entry *entry = &dictionary->entries[i];

        if (print_bytes(entry->key, entry->key_length) != 0 ||
            fputs(": ", stdout) == EOF ||
            print_bytes(entry->value, entry->value_length) != 0 ||
            fputc('\n', stdout) == EOF) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    Dictionary first;
    Dictionary second;
    Dictionary merged;
    int status = EXIT_FAILURE;

    dictionary_init(&first);
    dictionary_init(&second);
    dictionary_init(&merged);

    if (dictionary_set_n(&first,
                         "name",
                         sizeof("name") - 1,
                         "Alice",
                         sizeof("Alice") - 1) != 0 ||
        dictionary_set_n(&first,
                         "city",
                         sizeof("city") - 1,
                         "London",
                         sizeof("London") - 1) != 0 ||
        dictionary_set_n(&second,
                         "city",
                         sizeof("city") - 1,
                         "Paris",
                         sizeof("Paris") - 1) != 0 ||
        dictionary_set_n(&second,
                         "role",
                         sizeof("role") - 1,
                         "Developer",
                         sizeof("Developer") - 1) != 0) {
        fputs("Failed to create dictionaries.\n", stderr);
        goto cleanup;
    }

    if (dictionary_merge(&merged, &first, &second) != 0) {
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