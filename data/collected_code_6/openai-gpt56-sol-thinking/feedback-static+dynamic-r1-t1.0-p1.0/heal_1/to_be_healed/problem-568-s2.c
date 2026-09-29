#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t count;
    size_t capacity;
} Dictionary;

typedef struct {
    Dictionary *items;
    size_t count;
} DictionaryList;

int create_empty_dictionary_list(size_t count, DictionaryList **out_list)
{
    DictionaryList *list;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (out_list == NULL) {
        return EINVAL;
    }

    *out_list = NULL;

    if (count > SIZE_MAX / sizeof(Dictionary)) {
        return EOVERFLOW;
    }

    list = malloc(sizeof(*list));
    if (list == NULL) {
        return ENOMEM;
    }

    list->items = NULL;
    list->count = count;

    if (count > 0) {
        list->items = malloc(count * sizeof(*list->items));
        if (list->items == NULL) {
            free(list);
            return ENOMEM;
        }

        for (i = 0; i < count; ++i) {
            list->items[i].entries = NULL;
            list->items[i].count = 0;
            list->items[i].capacity = 0;
        }
    }

    *out_list = list;
    return 0;
}

void destroy_dictionary_list(DictionaryList *list)
{
    size_t i;
    size_t j;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < list->count; ++i) {
        for (j = 0; j < list->items[i].count; ++j) {
            free(list->items[i].entries[j].key);
            free(list->items[i].entries[j].value);
        }
        free(list->items[i].entries);
    }

    free(list->items);
    free(list);
}

int main(void)
{
    DictionaryList *list = NULL;
    int status = create_empty_dictionary_list(10, &list);

    if (status != 0) {
        fprintf(stderr, "Failed to create dictionary list: %d\n", status);
        return EXIT_FAILURE;
    }

    destroy_dictionary_list(list);
    return EXIT_SUCCESS;
}