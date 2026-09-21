#include <stddef.h>
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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    key_length = strlen(key);
    if (key_length >= buffer_size) {
        return DICTIONARY_BUFFER_TOO_SMALL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, key, key_length);
    buffer[key_length] = '\0';

    return DICTIONARY_SUCCESS;
}

int main(void) {
    static const DictionaryEntry entries[] = {
        {"name", "Alice"},
        {"age", "30"},
        {"city", "London"}
    };
    const Dictionary dictionary = {
        entries,
        sizeof(entries) / sizeof(entries[0])
    };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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