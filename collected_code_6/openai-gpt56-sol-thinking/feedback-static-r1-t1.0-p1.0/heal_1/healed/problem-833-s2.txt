#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    const char *key;
    size_t key_length;
} DictionaryEntry;

typedef struct {
    const DictionaryEntry *entries;
    size_t count;
} Dictionary;

static void free_key_list(char **keys, size_t count)
{
    size_t index;

    if (keys == NULL) {
        return;
    }

    for (index = 0; index < count; ++index) {
        free(keys[index]);
    }

    free(keys);
}

static int copy_key(const char *key, size_t length, char **copy_out)
{
    char *copy;
    size_t index;

    if (key == NULL || copy_out == NULL || length == SIZE_MAX) {
        return -1;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return -1;
    }

    for (index = 0; index < length; ++index) {
        if (key[index] == '\0') {
            free(copy);
            return -1;
        }

        copy[index] = key[index];
    }

    copy[length] = '\0';
    *copy_out = copy;
    return 0;
}

static int dictionary_get_keys(
    const Dictionary *dictionary,
    char ***keys_out,
    size_t *count_out)
{
    char **keys;
    size_t index;

    if (keys_out == NULL || count_out == NULL) {
        return -1;
    }

    *keys_out = NULL;
    *count_out = 0;

    if (dictionary == NULL ||
        (dictionary->count != 0 && dictionary->entries == NULL)) {
        return -1;
    }

    if (dictionary->count == 0) {
        return 0;
    }

    if (dictionary->count > SIZE_MAX / sizeof(*keys)) {
        return -1;
    }

    keys = calloc(dictionary->count, sizeof(*keys));
    if (keys == NULL) {
        return -1;
    }

    for (index = 0; index < dictionary->count; ++index) {
        const DictionaryEntry *entry = &dictionary->entries[index];

        if (copy_key(entry->key, entry->key_length, &keys[index]) != 0) {
            free_key_list(keys, index);
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
        {"name", sizeof("name") - 1},
        {"city", sizeof("city") - 1},
        {"language", sizeof("language") - 1}
    };
    const Dictionary dictionary = {
        entries,
        sizeof(entries) / sizeof(entries[0])
    };
    char **keys = NULL;
    size_t key_count = 0;
    size_t index;
    int status = EXIT_SUCCESS;

    if (dictionary_get_keys(&dictionary, &keys, &key_count) != 0) {
        return EXIT_FAILURE;
    }

    for (index = 0; index < key_count; ++index) {
        if (printf("%s\n", keys[index]) < 0) {
            status = EXIT_FAILURE;
            break;
        }
    }

    free_key_list(keys, key_count);

    if (fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    return status;
}