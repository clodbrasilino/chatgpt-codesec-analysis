#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *key;
    size_t key_length;
} DictionaryEntry;

typedef struct {
    const DictionaryEntry *entries;
    size_t count;
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

static void free_key_list(char **keys, size_t key_count)
{
    size_t i;

    if (keys == NULL) {
        return;
    }

    for (i = 0; i < key_count; ++i) {
        free(keys[i]);
    }

    free(keys);
}

static char **dictionary_keys(const Dictionary *dictionary, size_t *key_count)
{
    char **keys;
    size_t allocation_count;
    size_t i;

    if (key_count == NULL) {
        return NULL;
    }

    *key_count = 0;

    if (dictionary == NULL ||
        (dictionary->count > 0 && dictionary->entries == NULL)) {
        return NULL;
    }

    if (dictionary->count == SIZE_MAX) {
        return NULL;
    }

    allocation_count = dictionary->count + 1;

    if (allocation_count > SIZE_MAX / sizeof(*keys)) {
        return NULL;
    }

    keys = calloc(allocation_count, sizeof(*keys));
    if (keys == NULL) {
        return NULL;
    }

    for (i = 0; i < dictionary->count; ++i) {
        const DictionaryEntry *entry = &dictionary->entries[i];

        if (entry->key == NULL || entry->key_length == SIZE_MAX) {
            free_key_list(keys, i);
            return NULL;
        }

        keys[i] = duplicate_string(entry->key, entry->key_length);
        if (keys[i] == NULL) {
            free_key_list(keys, i);
            return NULL;
        }
    }

    keys[dictionary->count] = NULL;
    *key_count = dictionary->count;

    return keys;
}

int main(void)
{
    static const DictionaryEntry entries[] = {
        { "name", sizeof("name") - 1 },
        { "age", sizeof("age") - 1 },
        { "city", sizeof("city") - 1 }
    };

    const Dictionary dictionary = {
        entries,
        sizeof(entries) / sizeof(entries[0])
    };

    char **keys;
    size_t key_count;
    size_t i;

    keys = dictionary_keys(&dictionary, &key_count);
    if (keys == NULL) {
        fputs("Failed to retrieve dictionary keys.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < key_count; ++i) {
        if (puts(keys[i]) == EOF) {
            free_key_list(keys, key_count);
            return EXIT_FAILURE;
        }
    }

    free_key_list(keys, key_count);
    return EXIT_SUCCESS;
}