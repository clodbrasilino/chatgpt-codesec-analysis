#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    size_t key_length;
    long value;
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

    if (length > 0) {
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

static int add_overflows_long(long left, long right)
{
    if (right > 0) {
        return left > LONG_MAX - right;
    }

    if (right < 0) {
        return left < LONG_MIN - right;
    }

    return 0;
}

static int dictionary_add_n(Dictionary *dictionary,
                            const char *key,
                            size_t key_length,
                            long value)
{
    size_t i;
    char *key_copy;

    if (dictionary == NULL || key == NULL || key_length == SIZE_MAX) {
        return -1;
    }

    for (i = 0; i < dictionary->size; ++i) {
        Entry *entry = &dictionary->entries[i];

        if (entry->key_length != key_length) {
            continue;
        }

        if (key_length != 0 &&
            memcmp(entry->key, key, key_length) != 0) {
            continue;
        }

        if (add_overflows_long(entry->value, value)) {
            return -1;
        }

        entry->value += value;
        return 0;
    }

    if (dictionary->size == dictionary->capacity) {
        size_t new_capacity;

        if (dictionary->capacity == 0) {
            new_capacity = 4;
        } else {
            if (dictionary->capacity > SIZE_MAX / 2) {
                return -1;
            }

            new_capacity = dictionary->capacity * 2;
        }

        if (dictionary_reserve(dictionary, new_capacity) != 0) {
            return -1;
        }
    }

    key_copy = duplicate_string_n(key, key_length);
    if (key_copy == NULL) {
        return -1;
    }

    dictionary->entries[dictionary->size].key = key_copy;
    dictionary->entries[dictionary->size].key_length = key_length;
    dictionary->entries[dictionary->size].value = value;
    ++dictionary->size;

    return 0;
}

static int dictionary_add(Dictionary *dictionary,
                          const char *key,
                          long value)
{
    if (dictionary == NULL || key == NULL) {
        return -1;
    }

    return dictionary_add_n(dictionary, key, strlen(key), value);
}

static int dictionary_combine(const Dictionary *first,
                              const Dictionary *second,
                              Dictionary *result)
{
    Dictionary temporary;
    size_t i;

    if (first == NULL || second == NULL || result == NULL ||
        result == first || result == second) {
        return -1;
    }

    dictionary_init(&temporary);

    for (i = 0; i < first->size; ++i) {
        const Entry *entry = &first->entries[i];

        if (dictionary_add_n(&temporary,
                             entry->key,
                             entry->key_length,
                             entry->value) != 0) {
            dictionary_destroy(&temporary);
            return -1;
        }
    }

    for (i = 0; i < second->size; ++i) {
        const Entry *entry = &second->entries[i];

        if (dictionary_add_n(&temporary,
                             entry->key,
                             entry->key_length,
                             entry->value) != 0) {
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

    for (i = 0; i < dictionary->size; ++i) {
        const Entry *entry = &dictionary->entries[i];

        if (fwrite(entry->key, 1, entry->key_length, stdout) !=
            entry->key_length) {
            return -1;
        }

        if (printf(": %ld\n", entry->value) < 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    Dictionary first;
    Dictionary second;
    Dictionary combined;
    int status = EXIT_FAILURE;

    dictionary_init(&first);
    dictionary_init(&second);
    dictionary_init(&combined);

    if (dictionary_add_n(&first, "apple", sizeof("apple") - 1, 3) != 0 ||
        dictionary_add_n(&first, "banana", sizeof("banana") - 1, 5) != 0 ||
        dictionary_add_n(&second, "banana", sizeof("banana") - 1, 7) != 0 ||
        dictionary_add_n(&second, "orange", sizeof("orange") - 1, 4) != 0) {
        fprintf(stderr, "Failed to create dictionaries.\n");
        goto cleanup;
    }

    if (dictionary_combine(&first, &second, &combined) != 0) {
        fprintf(stderr, "Failed to combine dictionaries.\n");
        goto cleanup;
    }

    errno = 0;

    if (dictionary_print(&combined) != 0 || fflush(stdout) == EOF) {
        int error_number = errno;

        if (error_number != 0) {
            fprintf(stderr, "Failed to write output: %s\n",
                    strerror(error_number));
        } else {
            fprintf(stderr, "Failed to write output.\n");
        }

        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(&combined);
    dictionary_destroy(&second);
    dictionary_destroy(&first);

    return status;
}