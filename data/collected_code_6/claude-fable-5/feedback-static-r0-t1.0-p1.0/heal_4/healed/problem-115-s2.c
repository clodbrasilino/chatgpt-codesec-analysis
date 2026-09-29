#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_KEY_LEN 64
#define MAX_VAL_LEN 64

typedef struct {
    char key[MAX_KEY_LEN];
    char value[MAX_VAL_LEN];
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t count;
    size_t capacity;
} Dict;

typedef struct {
    Dict **dicts;
    size_t count;
} DictList;

Dict *dict_create(size_t capacity)
{
    Dict *d = malloc(sizeof(Dict));
    if (d == NULL) {
        return NULL;
    }
    d->count = 0;
    d->capacity = capacity;
    if (capacity > 0) {
        d->entries = calloc(capacity, sizeof(DictEntry));
        if (d->entries == NULL) {
            free(d);
            return NULL;
        }
    } else {
        d->entries = NULL;
    }
    return d;
}

int dict_add(Dict *d, const char *key, const char *value)
{
    if (d == NULL || key == NULL || value == NULL) {
        return -1;
    }
    if (d->count >= d->capacity) {
        return -1;
    }

    size_t key_len = strnlen(key, MAX_KEY_LEN);
    size_t val_len = strnlen(value, MAX_VAL_LEN);

    if (key_len >= MAX_KEY_LEN || val_len >= MAX_VAL_LEN) {
        return -1;
    }

    memcpy(d->entries[d->count].key, key, key_len);
    d->entries[d->count].key[key_len] = '\0';

    memcpy(d->entries[d->count].value, value, val_len);
    d->entries[d->count].value[val_len] = '\0';

    d->count++;
    return 0;
}

void dict_destroy(Dict *d)
{
    if (d != NULL) {
        free(d->entries);
        free(d);
    }
}

bool all_dicts_empty(const DictList *list)
{
    if (list == NULL || list->dicts == NULL) {
        return true;
    }
    for (size_t i = 0; i < list->count; i++) {
        if (list->dicts[i] != NULL && list->dicts[i]->count > 0) {
            return false;
        }
    }
    return true;
}

void dictlist_destroy(DictList *list)
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

DictList *dictlist_create(size_t count)
{
    DictList *list = malloc(sizeof(DictList));
    if (list == NULL) {
        return NULL;
    }
    list->count = count;
    if (count > 0) {
        list->dicts = calloc(count, sizeof(Dict *));
        if (list->dicts == NULL) {
            free(list);
            return NULL;
        }
    } else {
        list->dicts = NULL;
    }
    return list;
}

int main(void)
{
    DictList *list1 = dictlist_create(3);
    if (list1 == NULL) {
        fprintf(stderr, "Allocation failure\n");
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < list1->count; i++) {
        list1->dicts[i] = dict_create(4);
        if (list1->dicts[i] == NULL) {
            fprintf(stderr, "Allocation failure\n");
            dictlist_destroy(list1);
            return EXIT_FAILURE;
        }
    }

    if (all_dicts_empty(list1)) {
        printf("List 1: all dictionaries are empty\n");
    } else {
        printf("List 1: not all dictionaries are empty\n");
    }

    DictList *list2 = dictlist_create(3);
    if (list2 == NULL) {
        fprintf(stderr, "Allocation failure\n");
        dictlist_destroy(list1);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < list2->count; i++) {
        list2->dicts[i] = dict_create(4);
        if (list2->dicts[i] == NULL) {
            fprintf(stderr, "Allocation failure\n");
            dictlist_destroy(list1);
            dictlist_destroy(list2);
            return EXIT_FAILURE;
        }
    }

    if (dict_add(list2->dicts[1], "name", "alice") != 0) {
        fprintf(stderr, "Failed to add entry\n");
        dictlist_destroy(list1);
        dictlist_destroy(list2);
        return EXIT_FAILURE;
    }

    if (all_dicts_empty(list2)) {
        printf("List 2: all dictionaries are empty\n");
    } else {
        printf("List 2: not all dictionaries are empty\n");
    }

    dictlist_destroy(list1);
    dictlist_destroy(list2);
    return EXIT_SUCCESS;
}