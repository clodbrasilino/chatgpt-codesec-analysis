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

static int duplicate_string(const char *source, size_t source_length,
                            char **copy_out)
{
    char *copy;

    if (source == NULL || copy_out == NULL || source_length == SIZE_MAX) {
        return -1;
    }

    *copy_out = NULL;

    copy = malloc(source_length + 1U);
    if (copy == NULL) {
        return -1;
    }

    if (source_length > 0U) {
        memcpy(copy, source, source_length);
    }

    copy[source_length] = '\0';
    *copy_out = copy;

    return 0;
}

static void free_string_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0U; i < count; ++i) {
        free(list[i]);
    }

    free(list);
}

static int dictionary_keys(const Dictionary *dictionary,
                           char ***keys_out,
                           size_t *count_out)
{
    char **keys;
    size_t i;

    if (dictionary == NULL || keys_out == NULL || count_out == NULL) {
        return -1;
    }

    *keys_out = NULL;
    *count_out = 0U;

    if (dictionary->count == 0U) {
        return 0;
    }

    if (dictionary->entries == NULL ||
        dictionary->count > SIZE_MAX / sizeof(*keys)) {
        return -1;
    }

    keys = calloc(dictionary->count, sizeof(*keys));
    if (keys == NULL) {
        return -1;
    }

    for (i = 0U; i < dictionary->count; ++i) {
        const DictionaryEntry *entry = &dictionary->entries[i];

        if (entry->key == NULL ||
            entry->key_length == SIZE_MAX ||
            memchr(entry->key, '\0', entry->key_length) != NULL) {
            free_string_list(keys, i);
            return -1;
        }

        if (duplicate_string(entry->key, entry->key_length, &keys[i]) != 0) {
            free_string_list(keys, i);
            return -1;
        }
    }

    *keys_out = keys;
    *count_out = dictionary->count;

    return 0;
}

int main(void)
{
    static const DictionaryEntry entries[] = {
        {"name", sizeof("name") - 1U},
        {"language", sizeof("language") - 1U},
        {"level", sizeof("level") - 1U}
    };
    const Dictionary dictionary = {
        entries,
        sizeof(entries) / sizeof(entries[0])
    };
    char **keys = NULL;
    size_t key_count = 0U;
    size_t i;

    if (dictionary_keys(&dictionary, &keys, &key_count) != 0) {
        fputs("Failed to retrieve dictionary keys.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < key_count; ++i) {
        if (puts(keys[i]) == EOF) {
            free_string_list(keys, key_count);
            return EXIT_FAILURE;
        }
    }

    free_string_list(keys, key_count);
    return EXIT_SUCCESS;
}