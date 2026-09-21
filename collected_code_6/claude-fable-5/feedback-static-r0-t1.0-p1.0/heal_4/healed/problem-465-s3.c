#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *key;
    char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dict;

static char *dup_string(const char *src)
{
    size_t len;
    size_t alloc_size;
    char *dst;

    if (src == NULL) {
        return NULL;
    }

    len = strnlen(src, SIZE_MAX - 1);
    if (len >= SIZE_MAX - 1) {
        return NULL;
    }

    alloc_size = len + 1;
    dst = malloc(alloc_size);
    if (dst == NULL) {
        return NULL;
    }

    memcpy(dst, src, len);
    dst[len] = '\0';
    return dst;
}

static Dict *dict_create(size_t capacity)
{
    Dict *d;

    if (capacity == 0 || capacity > SIZE_MAX / sizeof(DictEntry)) {
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
    char *k;
    char *v;

    if (d == NULL || key == NULL || value == NULL) {
        return -1;
    }

    if (d->size >= d->capacity) {
        size_t new_capacity;
        DictEntry *tmp;

        if (d->capacity > SIZE_MAX / 2 / sizeof(DictEntry)) {
            return -1;
        }

        new_capacity = d->capacity * 2;
        tmp = realloc(d->entries, new_capacity * sizeof(DictEntry));
        if (tmp == NULL) {
            return -1;
        }
        d->entries = tmp;
        d->capacity = new_capacity;
    }

    k = dup_string(key);
    if (k == NULL) {
        return -1;
    }

    v = dup_string(value);
    if (v == NULL) {
        free(k);
        return -1;
    }

    d->entries[d->size].key = k;
    d->entries[d->size].value = v;
    d->size++;
    return 0;
}

static void dict_drop_empty_items(Dict *d)
{
    size_t write_index = 0;
    size_t i;

    if (d == NULL || d->entries == NULL) {
        return;
    }

    for (i = 0; i < d->size; i++) {
        if (d->entries[i].value != NULL && d->entries[i].value[0] != '\0') {
            if (write_index != i) {
                d->entries[write_index] = d->entries[i];
                d->entries[i].key = NULL;
                d->entries[i].value = NULL;
            }
            write_index++;
        } else {
            free(d->entries[i].key);
            free(d->entries[i].value);
            d->entries[i].key = NULL;
            d->entries[i].value = NULL;
        }
    }

    d->size = write_index;
}

static void dict_print(const Dict *d)
{
    size_t i;

    if (d == NULL || d->entries == NULL) {
        return;
    }

    printf("{");
    for (i = 0; i < d->size; i++) {
        printf("\"%s\": \"%s\"",
               d->entries[i].key != NULL ? d->entries[i].key : "",
               d->entries[i].value != NULL ? d->entries[i].value : "");
        if (i + 1 < d->size) {
            printf(", ");
        }
    }
    printf("}\n");
}

static void dict_destroy(Dict *d)
{
    size_t i;

    if (d == NULL) {
        return;
    }

    if (d->entries != NULL) {
        for (i = 0; i < d->size; i++) {
            free(d->entries[i].key);
            free(d->entries[i].value);
        }
        free(d->entries);
    }
    free(d);
}

int main(void)
{
    Dict *d = dict_create(4);

    if (d == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if (dict_add(d, "name", "Alice") != 0 ||
        dict_add(d, "city", "") != 0 ||
        dict_add(d, "email", "alice@example.com") != 0 ||
        dict_add(d, "phone", "") != 0 ||
        dict_add(d, "country", "USA") != 0) {
        fprintf(stderr, "Failed to add entries\n");
        dict_destroy(d);
        return EXIT_FAILURE;
    }

    printf("Before dropping empty items:\n");
    dict_print(d);

    dict_drop_empty_items(d);

    printf("After dropping empty items:\n");
    dict_print(d);

    dict_destroy(d);
    return EXIT_SUCCESS;
}