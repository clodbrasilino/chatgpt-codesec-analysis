#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *key;
    size_t key_length;
    const char *value;
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

static DictionaryStatus dictionary_key_buffer_size(
    const Dictionary *dictionary,
    size_t index,
    size_t *required_size
) {
    const DictionaryEntry *entry;

    if (dictionary == NULL || required_size == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    if (dictionary->entries == NULL || index >= dictionary->count) {
        return DICTIONARY_INDEX_OUT_OF_RANGE;
    }

    entry = &dictionary->entries[index];

    if (entry->key == NULL || entry->value == NULL || entry->key_length == SIZE_MAX) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    *required_size = entry->key_length + 1U;
    return DICTIONARY_SUCCESS;
}

static DictionaryStatus dictionary_key_at_index(
    const Dictionary *dictionary,
    size_t index,
    char *buffer,
    size_t buffer_size
) {
    const DictionaryEntry *entry;
    DictionaryStatus status;
    size_t required_size;
    size_t i;

    if (buffer == NULL || buffer_size == 0U) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    status = dictionary_key_buffer_size(dictionary, index, &required_size);
    if (status != DICTIONARY_SUCCESS) {
        return status;
    }

    if (buffer_size < required_size) {
        return DICTIONARY_BUFFER_TOO_SMALL;
    }

    entry = &dictionary->entries[index];

    for (i = 0U; i < entry->key_length; ++i) {
        buffer[i] = entry->key[i];
    }

    buffer[entry->key_length] = '\0';
    return DICTIONARY_SUCCESS;
}

int main(void) {
    static const DictionaryEntry entries[] = {
        {"name", sizeof("name") - 1U, "Alice"},
        {"age", sizeof("age") - 1U, "30"},
        {"city", sizeof("city") - 1U, "London"}
    };
    const Dictionary dictionary = {
        entries,
        sizeof(entries) / sizeof(entries[0])
    };
    DictionaryStatus status;
    size_t required_size;
    char *key;

    status = dictionary_key_buffer_size(&dictionary, 1U, &required_size);
    if (status != DICTIONARY_SUCCESS) {
        fputs("Unable to determine dictionary key size.\n", stderr);
        return EXIT_FAILURE;
    }

    key = malloc(required_size);
    if (key == NULL) {
        fputs("Unable to allocate memory for dictionary key.\n", stderr);
        return EXIT_FAILURE;
    }

    status = dictionary_key_at_index(&dictionary, 1U, key, required_size);
    if (status != DICTIONARY_SUCCESS) {
        free(key);
        fputs("Unable to access dictionary key.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", key) < 0) {
        free(key);
        return EXIT_FAILURE;
    }

    free(key);
    return EXIT_SUCCESS;
}