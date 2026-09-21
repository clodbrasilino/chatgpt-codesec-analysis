#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    const char *key;
    /* Possible weaknesses found:
     *  struct member 'DictionaryEntry::value' is never used. [unusedStructMember]
     */
    const char *value;
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
        (dictionary->count > 0 && dictionary->entries == NULL)) {
        return -1;
    }

    if (dictionary->count > (SIZE_MAX / sizeof(*keys)) - 1) {
        return -1;
    }

    keys = calloc(dictionary->count + 1, sizeof(*keys));
    if (keys == NULL) {
        return -1;
    }

    for (index = 0; index < dictionary->count; ++index) {
        const char *key = dictionary->entries[index].key;
        size_t length;

        if (key == NULL) {
            free_key_list(keys, index);
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        length = strlen(key);
        if (length == SIZE_MAX) {
            free_key_list(keys, index);
            return -1;
        }

        keys[index] = malloc(length + 1);
        if (keys[index] == NULL) {
            free_key_list(keys, index);
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(keys[index], key, length + 1);
    }

    *keys_out = keys;
    *count_out = dictionary->count;
    return 0;
}

int main(void)
{
    const DictionaryEntry entries[] = {
        {"name", "Alice"},
        {"city", "London"},
        {"language", "C"}
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