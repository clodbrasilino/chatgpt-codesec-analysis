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

    d->entries = calloc(capacity, sizeof(DictEntry));
    if (d->entries == NULL) {
        free(d);
        return NULL;
    }

    d->size = 0;
    d->capacity = capacity;
    return d;
}

static char *duplicate_string(const char *s)
{
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }

    len = strlen(s);
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, s, len + 1);
    return copy;
}

static int dict_add(Dict *d, const char *key, const char *value)
{
    char *k;
    char *v;

    if (d == NULL || key == NULL || value == NULL) {
        return -1;
    }

    if (d->size >= d->capacity) {
        return -1;
    }

    k = duplicate_string(key);
    if (k == NULL) {
        return -1;
    }

    v = duplicate_string(value);
    if (v == NULL) {
        free(k);
        return -1;
    }

    d->entries[d->size].key = k;
    d->entries[d->size].value = v;
    d->size++;
    return 0;
}

static const char *dict_key_by_index(const Dict *d, size_t index)
{
    if (d == NULL || index >= d->size) {
        return NULL;
    }
    return d->entries[index].key;
}

static const char *dict_value_by_index(const Dict *d, size_t index)
{
    if (d == NULL || index >= d->size) {
        return NULL;
    }
    return d->entries[index].value;
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
    const char *key;
    const char *value;
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
        key = dict_key_by_index(d, i);
        value = dict_value_by_index(d, i);
        if (key == NULL || value == NULL) {
            fprintf(stderr, "Invalid index access at %zu\n", i);
            dict_destroy(d);
            return EXIT_FAILURE;
        }
        printf("Index %zu: key=%s, value=%s\n", i, key, value);
    }

    key = dict_key_by_index(d, 100);
    if (key == NULL) {
        printf("Index 100 is out of range\n");
    }

    dict_destroy(d);
    return EXIT_SUCCESS;
}