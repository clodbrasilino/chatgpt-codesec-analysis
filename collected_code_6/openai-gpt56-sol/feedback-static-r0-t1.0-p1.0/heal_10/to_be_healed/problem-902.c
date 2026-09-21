#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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

static char *duplicate_string(const char *source, size_t length)
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
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static int dictionary_init(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return -1;
    }

    dictionary->entries = NULL;
    dictionary->size = 0;
    dictionary->capacity = 0;
    return 0;
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
    dictionary->entries = NULL;
    dictionary->size = 0;
    dictionary->capacity = 0;
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

static int dictionary_add(Dictionary *dictionary,
                          const char *key,
                          size_t key_length,
                          long value)
{
    size_t index;
    char *key_copy;

    if (dictionary == NULL || key == NULL || key_length == SIZE_MAX) {
        return -1;
    }

    if (key_length > 0 && memchr(key, '\0', key_length) != NULL) {
        return -1;
    }

    index = dictionary_find(dictionary, key, key_length);
    if (index != SIZE_MAX) {
        long current = dictionary->entries[index].value;

        if ((value > 0 && current > LONG_MAX - value) ||
            (value < 0 && current < LONG_MIN - value)) {
            return -1;
        }

        dictionary->entries[index].value = current + value;
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

    key_copy = duplicate_string(key, key_length);
    if (key_copy == NULL) {
        return -1;
    }

    dictionary->entries[dictionary->size].key = key_copy;
    dictionary->entries[dictionary->size].key_length = key_length;
    dictionary->entries[dictionary->size].value = value;
    ++dictionary->size;

    return 0;
}

static int dictionary_combine(const Dictionary *first,
                              const Dictionary *second,
                              Dictionary *result)
{
    Dictionary combined;
    size_t total;
    size_t i;

    if (first == NULL || second == NULL || result == NULL ||
        result == first || result == second) {
        return -1;
    }

    if (dictionary_init(&combined) != 0) {
        return -1;
    }

    if (first->size > SIZE_MAX - second->size) {
        return -1;
    }

    total = first->size + second->size;

    if (total > 0 && dictionary_reserve(&combined, total) != 0) {
        dictionary_destroy(&combined);
        return -1;
    }

    for (i = 0; i < first->size; ++i) {
        const Entry *entry = &first->entries[i];

        if (dictionary_add(&combined, entry->key, entry->key_length,
                           entry->value) != 0) {
            dictionary_destroy(&combined);
            return -1;
        }
    }

    for (i = 0; i < second->size; ++i) {
        const Entry *entry = &second->entries[i];

        if (dictionary_add(&combined, entry->key, entry->key_length,
                           entry->value) != 0) {
            dictionary_destroy(&combined);
            return -1;
        }
    }

    dictionary_destroy(result);
    *result = combined;
    return 0;
}

static int print_escaped_key(const char *key, size_t length)
{
    static const char hex[] = "0123456789abcdef";
    size_t i;

    if (key == NULL) {
        return -1;
    }

    for (i = 0; i < length; ++i) {
        unsigned char byte = (unsigned char)key[i];

        if (byte == '"' || byte == '\\') {
            if (fputc('\\', stdout) == EOF ||
                fputc((int)byte, stdout) == EOF) {
                return -1;
            }
        } else if (byte >= 0x20 && byte <= 0x7e) {
            if (fputc((int)byte, stdout) == EOF) {
                return -1;
            }
        } else {
            if (fputs("\\u00", stdout) == EOF ||
                fputc((int)hex[byte >> 4], stdout) == EOF ||
                fputc((int)hex[byte & 0x0f], stdout) == EOF) {
                return -1;
            }
        }
    }

    return 0;
}

static int dictionary_print(const Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return -1;
    }

    if (fputc('{', stdout) == EOF) {
        return -1;
    }

    for (i = 0; i < dictionary->size; ++i) {
        const Entry *entry = &dictionary->entries[i];

        if (i > 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (fputc('"', stdout) == EOF ||
            print_escaped_key(entry->key, entry->key_length) != 0 ||
            printf("\": %ld", entry->value) < 0) {
            return -1;
        }
    }

    if (fputs("}\n", stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    Dictionary first;
    Dictionary second;
    Dictionary result;
    int status = EXIT_FAILURE;

    if (dictionary_init(&first) != 0) {
        return EXIT_FAILURE;
    }

    if (dictionary_init(&second) != 0) {
        dictionary_destroy(&first);
        return EXIT_FAILURE;
    }

    if (dictionary_init(&result) != 0) {
        dictionary_destroy(&second);
        dictionary_destroy(&first);
        return EXIT_FAILURE;
    }

    if (dictionary_add(&first, "apple", sizeof("apple") - 1, 3) != 0 ||
        dictionary_add(&first, "banana", sizeof("banana") - 1, 5) != 0 ||
        dictionary_add(&second, "banana", sizeof("banana") - 1, 7) != 0 ||
        dictionary_add(&second, "orange", sizeof("orange") - 1, 4) != 0) {
        goto cleanup;
    }

    if (dictionary_combine(&first, &second, &result) != 0) {
        goto cleanup;
    }

    if (dictionary_print(&result) != 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    dictionary_destroy(&result);
    dictionary_destroy(&second);
    dictionary_destroy(&first);
    return status;
}