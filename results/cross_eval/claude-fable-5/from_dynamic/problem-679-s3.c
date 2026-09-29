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
} Dict;

static Dict *dict_create(size_t capacity)
{
    Dict *d;

    if (capacity == 0) {
        return NULL;
    }

    d = malloc(sizeof(Dict));
    if (d == NULL) {
        return NULL;
    }

    d->entries = malloc(capacity * sizeof(DictEntry));
    if (d->entries == NULL) {
        free(d);
        return NULL;
    }

    d->size = 0;
    d->capacity = capacity;
    return d;
}

static int dict_add(Dict *d, const char *key, const char *value)
{
    char *key_copy;
    char *value_copy;

    if (d == NULL || key == NULL || value == NULL) {
        return -1;
    }

    if (d->size >= d->capacity) {
        return -1;
    }

    key_copy = malloc(strlen(key) + 1);
    if (key_copy == NULL) {
        return -1;
    }
    strcpy(key_copy, key);

    value_copy = malloc(strlen(value) + 1);
    if (value_copy == NULL) {
        free(key_copy);
        return -1;
    }
    strcpy(value_copy, value);

    d->entries[d->size].key = key_copy;
    d->entries[d->size].value = value_copy;
    d->size++;
    return 0;
}

static const DictEntry *dict_get_by_index(const Dict *d, size_t index)
{
    if (d == NULL || index >= d->size) {
        return NULL;
    }
    return &d->entries[index];
}

static void dict_destroy(Dict *d)
{
    size_t i;

    if (d == NULL) {
        return;
    }

    for (i = 0; i < d->size; i++) {
        free(d->entries[i].key);
        free(d->entries[i].value);
    }
    free(d->entries);
    free(d);
}

int main(void)
{
    Dict *d;
    const DictEntry *entry;
    size_t i;

    d = dict_create(8);
    if (d == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if (dict_add(d, "apple", "fruit") != 0 ||
        dict_add(d, "carrot", "vegetable") != 0 ||
        dict_add(d, "salmon", "fish") != 0) {
        fprintf(stderr, "Failed to add entries\n");
        dict_destroy(d);
        return EXIT_FAILURE;
    }

    for (i = 0; i < d->size; i++) {
        entry = dict_get_by_index(d, i);
        if (entry != NULL) {
            printf("Index %zu: key=%s, value=%s\n", i, entry->key, entry->value);
        }
    }

    entry = dict_get_by_index(d, 100);
    if (entry == NULL) {
        printf("Index 100 is out of range\n");
    }

    dict_destroy(d);
    return EXIT_SUCCESS;
}