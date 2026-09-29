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
    bool *result)
{
    size_t i;

    if (result == NULL || (dictionaries == NULL && dictionary_count != 0U)) {
        return CHECK_INVALID_ARGUMENT;
    }

    *result = true;

    for (i = 0U; i < dictionary_count; ++i) {
        if (dictionaries[i].entry_count != 0U) {
            if (dictionaries[i].entries == NULL) {
                return CHECK_INVALID_ARGUMENT;
            }

            *result = false;
            break;
        }
    }

    return CHECK_SUCCESS;
}

int main(void)
{
    const DictionaryEntry entry = {"name", "Alice"};
    const Dictionary dictionaries[] = {
        {NULL, 0U},
        {NULL, 0U},
        {&entry, 1U}
    };
    bool result;
    CheckStatus status;

    status = all_dictionaries_empty(
        dictionaries,
        sizeof(dictionaries) / sizeof(dictionaries[0]),
        &result);

    if (status != CHECK_SUCCESS) {
        if (fputs("Unable to check dictionaries.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (fputs(result
                  ? "All dictionaries are empty.\n"
                  : "Not all dictionaries are empty.\n",
              stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}