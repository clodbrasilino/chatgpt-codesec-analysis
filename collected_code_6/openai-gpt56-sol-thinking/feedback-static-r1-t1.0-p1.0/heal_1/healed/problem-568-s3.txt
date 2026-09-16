#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char **keys;
    char **values;
    size_t size;
} Dictionary;

typedef struct {
    Dictionary *items;
    size_t count;
} DictionaryList;

DictionaryList *dictionary_list_create(size_t count)
{
    DictionaryList *list = malloc(sizeof(*list));

    if (list == NULL) {
        return NULL;
    }

    list->items = NULL;
    list->count = 0;

    if (count == 0) {
        return list;
    }

    if (count > SIZE_MAX / sizeof(*list->items)) {
        free(list);
        return NULL;
    }

    list->items = calloc(count, sizeof(*list->items));
    if (list->items == NULL) {
        free(list);
        return NULL;
    }

    list->count = count;
    return list;
}

void dictionary_list_destroy(DictionaryList *list)
{
    size_t i;
    size_t j;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < list->count; ++i) {
        Dictionary *dictionary = &list->items[i];

        for (j = 0; j < dictionary->size; ++j) {
            free(dictionary->keys[j]);
            free(dictionary->values[j]);
        }

        free(dictionary->keys);
        free(dictionary->values);
    }

    free(list->items);
    free(list);
}

int main(void)
{
    const size_t dictionary_count = 10;
    DictionaryList *list = dictionary_list_create(dictionary_count);

    if (list == NULL) {
        fputs("Failed to create dictionary list.\n", stderr);
        return EXIT_FAILURE;
    }

    dictionary_list_destroy(list);
    return EXIT_SUCCESS;
}