#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

typedef struct {
    Dictionary **dicts;
    size_t count;
} DictList;

static Dictionary *dict_create(void)
{
    Dictionary *d = malloc(sizeof(Dictionary));
    if (d == NULL) {
        return NULL;
    }
    d->entries = NULL;
    d->size = 0;
    d->capacity = 0;
    return d;
}

static void dict_destroy(Dictionary *d)
{
    if (d == NULL) {
        return;
    }
    for (size_t i = 0; i < d->size; i++) {
        free(d->entries[i].key);
        free(d->entries[i].value);
    }
    free(d->entries);
    free(d);
}

static void dict_list_destroy(DictList *list)
{
    if (list == NULL) {
        return;
    }
    if (list->dicts != NULL) {
        for (size_t i = 0; i < list->count; i++) {
            dict_destroy(list->dicts[i]);
        }
        free(list->dicts);
    }
    free(list);
}

static DictList *create_list_of_empty_dicts(size_t n)
{
    DictList *list = malloc(sizeof(DictList));
    if (list == NULL) {
        return NULL;
    }
    list->count = 0;
    list->dicts = NULL;

    if (n == 0) {
        return list;
    }

    if (n > SIZE_MAX / sizeof(Dictionary *)) {
        free(list);
        return NULL;
    }

    list->dicts = malloc(n * sizeof(Dictionary *));
    if (list->dicts == NULL) {
        free(list);
        return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        Dictionary *d = dict_create();
        if (d == NULL) {
            dict_list_destroy(list);
            return NULL;
        }
        list->dicts[i] = d;
        list->count = i + 1;
    }

    return list;
}

int main(void)
{
    size_t n = 5;
    DictList *list = create_list_of_empty_dicts(n);
    if (list == NULL) {
        fprintf(stderr, "Failed to create list of dictionaries\n");
        return EXIT_FAILURE;
    }

    printf("Created a list of %zu empty dictionaries\n", list->count);
    for (size_t i = 0; i < list->count; i++) {
        printf("Dictionary %zu: size = %zu\n", i, list->dicts[i]->size);
    }

    dict_list_destroy(list);
    return EXIT_SUCCESS;
}