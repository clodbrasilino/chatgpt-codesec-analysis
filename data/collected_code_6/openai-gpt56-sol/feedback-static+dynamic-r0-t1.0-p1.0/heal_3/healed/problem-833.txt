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

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0U) {
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static void free_string_list(char **list, size_t count)
{
    size_t index;

    if (list == NULL) {
        return;
    }

    for (index = 0U; index < count; ++index) {
        free(list[index]);
    }

    free(list);
}

static int dictionary_get_keys(
    const Dictionary *dictionary,
    char ***keys,
    size_t *key_count)
{
    char **result;
    size_t index;

    if (dictionary == NULL || keys == NULL || key_count == NULL) {
        return -1;
    }

    *keys = NULL;
    *key_count = 0U;

    if (dictionary->count == 0U) {
        return 0;
    }

    if (dictionary->entries == NULL ||
        dictionary->count > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = calloc(dictionary->count, sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    for (index = 0U; index < dictionary->count; ++index) {
        const DictionaryEntry *entry = &dictionary->entries[index];

        if (entry->key == NULL ||
            entry->key_length == SIZE_MAX ||
            strnlen(entry->key, entry->key_length) != entry->key_length) {
            free_string_list(result, index);
            return -1;
        }

        result[index] = duplicate_string(entry->key, entry->key_length);
        if (result[index] == NULL) {
            free_string_list(result, index);
            return -1;
        }
    }

    *keys = result;
    *key_count = dictionary->count;
    return 0;
}

int main(void)
{
    static const DictionaryEntry entries[] = {
        {"name", sizeof("name") - 1U},
        {"age", sizeof("age") - 1U},
        {"city", sizeof("city") - 1U}
    };
    const Dictionary dictionary = {
        entries,
        sizeof(entries) / sizeof(entries[0])
    };
    char **keys = NULL;
    size_t key_count = 0U;
    size_t index;

    if (dictionary_get_keys(&dictionary, &keys, &key_count) != 0) {
        fputs("Failed to retrieve dictionary keys.\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0U; index < key_count; ++index) {
        if (puts(keys[index]) == EOF) {
            free_string_list(keys, key_count);
            return EXIT_FAILURE;
        }
    }

    free_string_list(keys, key_count);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}