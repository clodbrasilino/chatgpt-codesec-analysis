#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'DictionaryEntry::key' is never used. [unusedStructMember]
     */
    const char *key;
    int value;
} DictionaryEntry;

typedef struct {
    const DictionaryEntry *entries;
    size_t count;
} Dictionary;

typedef enum {
    DICTIONARY_SUCCESS = 0,
    DICTIONARY_INVALID_ARGUMENT
} DictionaryStatus;

DictionaryStatus dictionary_all_values_same(
    const Dictionary *dictionary,
    bool *all_same
);

DictionaryStatus dictionary_all_values_same(
    const Dictionary *dictionary,
    bool *all_same
)
{
    size_t index;

    if (dictionary == NULL || all_same == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    if (dictionary->count > 0U && dictionary->entries == NULL) {
        return DICTIONARY_INVALID_ARGUMENT;
    }

    *all_same = true;

    for (index = 1U; index < dictionary->count; ++index) {
        if (dictionary->entries[index].value != dictionary->entries[0].value) {
            *all_same = false;
            break;
        }
    }

    return DICTIONARY_SUCCESS;
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
    if (status != DICTIONARY_SUCCESS) {
        if (fputs("Unable to check dictionary values.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("All values are the same: %s\n", all_same ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}