#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 4096

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dict;

static char *dup_string(const char *s)
{
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }

    len = strnlen(s, MAX_STRING_LEN);
    if (len >= MAX_STRING_LEN) {
        return NULL;
    }

    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, s, len);
    copy[len] = '\0';
    return copy;
}

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

    key_copy = dup_string(key);
    if (key_copy == NULL) {
        return -1;
    }

    value_copy = dup_string(value);
    if (value_copy == NULL) {
        free(key_copy);
        return -1;
    }

    d->entries[d->size].key = key_copy;
    d->entries[d->size].value = value_copy;
    d->size++;
    return 0;
}

static const char *dict_key_by_index(const Dict *d, size_t index)
{
    if (d == NULL) {
        return NULL;
    }

    if (index >= d->size) {
        return NULL;
    }

    return d->entries[index].key;
}

static const char *dict_value_by_index(const Dict *d, size_t index)
{
    if (d == NULL) {
        return NULL;
    }

    if (index >= d->size) {
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
    size_t i;

    d = dict_create(10);
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
        const char *value;

        key = dict_key_by_index(d, i);
        value = dict_value_by_index(d, i);
        if (key == NULL || value == NULL) {
            fprintf(stderr, "Invalid index access\n");
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