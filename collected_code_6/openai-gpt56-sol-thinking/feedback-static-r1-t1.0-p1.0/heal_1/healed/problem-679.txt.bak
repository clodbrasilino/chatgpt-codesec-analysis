#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *key;
} DictionaryEntry;

typedef struct {
    const DictionaryEntry *entries;
    size_t count;
} Dictionary;

typedef enum {
    DICTIONARY_SUCCESS = 0,
    DICTIONARY_INVALID_ARGUMENT,
    DICTIONARY_INDEX_OUT_OF_RANGE,
    DICTIONARY_BUFFER_TOO_SMALL
} DictionaryStatus;

DictionaryStatus dictionary_key_at_index(
    const Dictionary *dictionary,
    size_t index,
    char *buffer,
    size_t buffer_size
) {
    const char *key;
    size_t key_length;

    if (dictionary == NULL || buffer == NULL || buffer_size == 0U) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    if (dictionary->entries == NULL || index >= dictionary->count) {
        return DICTIONARY_INDEX_OUT_OF_RANGE;
    }

    key = dictionary->entries[index].key;
    if (key == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    key_length = strlen(key);
    if (key_length >= buffer_size) {
        return DICTIONARY_BUFFER_TOO_SMALL;
    }

    memcpy(buffer, key, key_length + 1U);

    return DICTIONARY_SUCCESS;
}

int main(void) {
    static const DictionaryEntry entries[] = {
        {"name"},
        {"age"},
        {"city"}
    };

    const Dictionary dictionary = {
        entries,
        sizeof(entries) / sizeof(entries[0])
    };

    char key[32];
    DictionaryStatus status;

    status = dictionary_key_at_index(&dictionary, 1U, key, sizeof(key));
    if (status != DICTIONARY_SUCCESS) {
        fputs("Unable to access dictionary key.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", key) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}