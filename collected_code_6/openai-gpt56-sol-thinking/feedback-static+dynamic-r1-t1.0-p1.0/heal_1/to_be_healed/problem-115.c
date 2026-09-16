#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'DictionaryEntry::key' is never used. [unusedStructMember]
     */
    const char *key;
    /* Possible weaknesses found:
     *  struct member 'DictionaryEntry::value' is never used. [unusedStructMember]
     */
    const char *value;
} DictionaryEntry;

typedef struct {
    const DictionaryEntry *entries;
    size_t entry_count;
} Dictionary;

typedef enum {
    CHECK_SUCCESS,
    CHECK_INVALID_ARGUMENT
} CheckStatus;

static CheckStatus all_dictionaries_empty(
    const Dictionary *dictionaries,
    size_t dictionary_count,
    bool *all_empty)
{
    size_t i;

    if (all_empty == NULL ||
        (dictionaries == NULL && dictionary_count != 0U)) {
        return CHECK_INVALID_ARGUMENT;
    }

    for (i = 0U; i < dictionary_count; ++i) {
        if (dictionaries[i].entry_count != 0U &&
            dictionaries[i].entries == NULL) {
            return CHECK_INVALID_ARGUMENT;
        }
    }

    *all_empty = true;

    for (i = 0U; i < dictionary_count; ++i) {
        if (dictionaries[i].entry_count != 0U) {
            *all_empty = false;
            break;
        }
    }

    return CHECK_SUCCESS;
}

int main(void)
{
    static const DictionaryEntry entries[] = {
        {"language", "C"}
    };
    static const Dictionary dictionaries[] = {
        {NULL, 0U},
        {entries, sizeof(entries) / sizeof(entries[0])},
        {NULL, 0U}
    };
    bool all_empty;
    CheckStatus status;

    status = all_dictionaries_empty(
        dictionaries,
        sizeof(dictionaries) / sizeof(dictionaries[0]),
        &all_empty);

    if (status != CHECK_SUCCESS) {
        return EXIT_FAILURE;
    }

    if (puts(all_empty
                 ? "All dictionaries are empty."
                 : "Not all dictionaries are empty.") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}