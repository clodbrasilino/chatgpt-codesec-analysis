#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *key;
    int value;
} DictionaryEntry;

typedef struct {
    const DictionaryEntry *entries;
    size_t count;
} Dictionary;

typedef enum {
    DICTIONARY_OK = 0,
    DICTIONARY_INVALID_ARGUMENT
} DictionaryStatus;

DictionaryStatus dictionary_all_values_same(
    const Dictionary *dictionary,
    bool *all_same)
{
    size_t i;

    if (dictionary == NULL || all_same == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    if (dictionary->count > 0U && dictionary->entries == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    *all_same = true;

    for (i = 0U; i < dictionary->count; ++i) {
        if (dictionary->entries[i].key == NULL) {
            return DICTIONARY_INVALID_ARGUMENT;
        }

        if (i > 0U &&
            dictionary->entries[i].value != dictionary->entries[0].value) {
            *all_same = false;
            break;
        }
    }

    return DICTIONARY_OK;
}

int main(void)
{
    const DictionaryEntry entries[] = {
        {"first", 42},
        {"second", 42},
        {"third", 42}
    };
    const Dictionary dictionary = {
        entries,
        sizeof(entries) / sizeof(entries[0])
    };
    bool all_same;
    DictionaryStatus status;

    status = dictionary_all_values_same(&dictionary, &all_same);
    if (status != DICTIONARY_OK) {
        if (fprintf(stderr, "Failed to inspect the dictionary.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("All values are the same: %s\n",
               all_same ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}