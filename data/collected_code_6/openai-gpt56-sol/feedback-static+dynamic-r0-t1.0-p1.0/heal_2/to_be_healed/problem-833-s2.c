#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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

static int duplicate_string(const char *source, char **copy_out)
{
    size_t length;
    char *copy;

    if (source == NULL || copy_out == NULL) {
        return -1;
    }

    *copy_out = NULL;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(source);

    if (length > SIZE_MAX - 1U) {
        return -1;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return -1;
    }

    if (length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

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
        if (duplicate_string(dictionary->entries[i].key, &keys[i]) != 0) {
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
        {"name", "Alice"},
        {"language", "C"},
        {"level", "experienced"}
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