#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct DictionaryEntry DictionaryEntry;

typedef struct {
    DictionaryEntry *head;
} Dictionary;

typedef struct {
    Dictionary *items;
    size_t count;
} DictionaryList;

typedef enum {
    CHECK_SUCCESS,
    CHECK_INVALID_ARGUMENT
} CheckStatus;

static CheckStatus all_dictionaries_empty(const DictionaryList *list, bool *result)
{
    size_t i;

    if (list == NULL || result == NULL) {
        return CHECK_INVALID_ARGUMENT;
    }

    if (list->count > 0U && list->items == NULL) {
        return CHECK_INVALID_ARGUMENT;
    }

    *result = true;

    for (i = 0U; i < list->count; ++i) {
        if (list->items[i].head != NULL) {
            *result = false;
            break;
        }
    }

    return CHECK_SUCCESS;
}

int main(void)
{
    Dictionary dictionaries[] = {
        {NULL},
        {NULL},
        {NULL}
    };
    DictionaryList list = {
        dictionaries,
        sizeof(dictionaries) / sizeof(dictionaries[0])
    };
    bool all_empty = false;
    CheckStatus status;

    status = all_dictionaries_empty(&list, &all_empty);
    if (status != CHECK_SUCCESS) {
        return EXIT_FAILURE;
    }

    if (puts(all_empty ? "All dictionaries are empty."
                       : "Not all dictionaries are empty.") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}