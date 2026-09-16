#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *key;
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
    size_t dictionary_index;
    size_t entry_index;

    if (all_empty == NULL ||
        (dictionaries == NULL && dictionary_count != 0U)) {
        return CHECK_INVALID_ARGUMENT;
    }

    *all_empty = true;

    for (dictionary_index = 0U;
         dictionary_index < dictionary_count;
         ++dictionary_index) {
        const Dictionary *dictionary = &dictionaries[dictionary_index];

        if (dictionary->entry_count != 0U && dictionary->entries == NULL) {
            return CHECK_INVALID_ARGUMENT;
        }

        for (entry_index = 0U;
             entry_index < dictionary->entry_count;
             ++entry_index) {
            const DictionaryEntry *entry = &dictionary->entries[entry_index];

            if (entry->key == NULL || entry->value == NULL) {
                return CHECK_INVALID_ARGUMENT;
            }
        }

        if (dictionary->entry_count != 0U) {
            *all_empty = false;
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
    bool all_empty = false;
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