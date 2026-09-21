#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LENGTH 4096U

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

    if (source == NULL || length > MAX_KEY_LENGTH ||
        length > SIZE_MAX - 1U) {
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

static char **dictionary_keys(const Dictionary *dictionary, size_t *key_count)
{
    char **keys;
    size_t i;

    if (key_count == NULL) {
        return NULL;
    }

    *key_count = 0U;

    if (dictionary == NULL ||
        (dictionary->count != 0U && dictionary->entries == NULL)) {
        return NULL;
    }

    if (dictionary->count > (SIZE_MAX / sizeof(*keys)) - 1U) {
        return NULL;
    }

    keys = calloc(dictionary->count + 1U, sizeof(*keys));
    if (keys == NULL) {
        return NULL;
    }

    for (i = 0U; i < dictionary->count; ++i) {
        const DictionaryEntry *entry = &dictionary->entries[i];

        if (entry->key == NULL ||
            entry->key_length > MAX_KEY_LENGTH ||
            memchr(entry->key, '\0', entry->key_length) != NULL) {
            goto failure;
        }

        keys[i] = duplicate_string(entry->key, entry->key_length);
        if (keys[i] == NULL) {
            goto failure;
        }
    }

    keys[dictionary->count] = NULL;
    *key_count = dictionary->count;
    return keys;

failure:
    while (i != 0U) {
        --i;
        free(keys[i]);
    }

    free(keys);
    return NULL;
}

static void free_key_list(char **keys, size_t key_count)
{
    size_t i;

    if (keys == NULL) {
        return;
    }

    for (i = 0U; i < key_count; ++i) {
        free(keys[i]);
    }

    free(keys);
}

int main(void)
{
    static const DictionaryEntry entries[] = {
        { "name", sizeof("name") - 1U },
        { "age", sizeof("age") - 1U },
        { "city", sizeof("city") - 1U }
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

    for (i = 0U; i < key_count; ++i) {
        if (puts(keys[i]) == EOF) {
            free_key_list(keys, key_count);
            return EXIT_FAILURE;
        }
    }

    free_key_list(keys, key_count);
    return EXIT_SUCCESS;
}