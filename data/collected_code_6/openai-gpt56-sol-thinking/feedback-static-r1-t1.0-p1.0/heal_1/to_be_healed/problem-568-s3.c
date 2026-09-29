#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char **keys;
    char **values;
    size_t size;
    /* Possible weaknesses found:
     *  struct member 'Dictionary::capacity' is never used. [unusedStructMember]
     */
    size_t capacity;
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
        for (j = 0; j < list->items[i].size; ++j) {
            free(list->items[i].keys[j]);
            free(list->items[i].values[j]);
        }

        free(list->items[i].keys);
        free(list->items[i].values);
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