#include <stdint.h>
#include <stddef.h>
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

DictionaryList *create_empty_dictionary_list(size_t count)
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

    list->items = malloc(count * sizeof(*list->items));
    if (list->items == NULL) {
        free(list);
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        list->items[i].entries = NULL;
        list->items[i].count = 0;
        list->items[i].capacity = 0;
    }

    list->count = count;
    return list;
}

void destroy_dictionary_list(DictionaryList *list)
{
    if (list == NULL) {
        return;
    }

    for (size_t i = 0; i < list->count; ++i) {
        for (size_t j = 0; j < list->items[i].count; ++j) {
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
    DictionaryList *list = create_empty_dictionary_list(10);

    if (list == NULL) {
        return EXIT_FAILURE;
    }

    destroy_dictionary_list(list);
    return EXIT_SUCCESS;
}