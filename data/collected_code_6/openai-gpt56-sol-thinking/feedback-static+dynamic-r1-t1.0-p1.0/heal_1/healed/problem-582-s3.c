#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define DICTIONARY_CAPACITY 16U

typedef struct {
    const char *key;
    const char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry entries[DICTIONARY_CAPACITY];
    size_t count;
} Dictionary;

typedef enum {
    DICTIONARY_SUCCESS = 0,
    DICTIONARY_INVALID_ARGUMENT,
    DICTIONARY_INVALID_STATE
} DictionaryStatus;

DictionaryStatus dictionary_is_empty(const Dictionary *dictionary, bool *is_empty)
{
    size_t index;

    if (dictionary == NULL || is_empty == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    if (dictionary->count > DICTIONARY_CAPACITY) {
        return DICTIONARY_INVALID_STATE;
    }

    for (index = 0U; index < dictionary->count; ++index) {
        if (dictionary->entries[index].key == NULL ||
            dictionary->entries[index].value == NULL) {
            return DICTIONARY_INVALID_STATE;
        }
    }

    *is_empty = dictionary->count == 0U;
    return DICTIONARY_SUCCESS;
}

int main(void)
{
    Dictionary dictionary = {0};
    bool is_empty = false;
    DictionaryStatus status;

    status = dictionary_is_empty(&dictionary, &is_empty);
    if (status != DICTIONARY_SUCCESS) {
        return EXIT_FAILURE;
    }

    if (puts(is_empty ? "Dictionary is empty."
                      : "Dictionary is not empty.") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}