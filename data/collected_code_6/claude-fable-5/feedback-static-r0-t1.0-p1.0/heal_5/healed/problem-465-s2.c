#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LEN 4096

typedef struct {
    char *key;
    char *value;
} DictItem;

typedef struct {
    DictItem *items;
    size_t count;
    size_t capacity;
} Dict;

static Dict *dict_create(void)
{
    Dict *d = malloc(sizeof(Dict));
    if (d == NULL) {
        return NULL;
    }
    d->items = NULL;
    d->count = 0;
    d->capacity = 0;
    return d;
}

static char *duplicate_string(const char *s)
{
    size_t len;
    size_t alloc_size;
    size_t i;
    char *copy;

    if (s == NULL) {
        return NULL;
    }

    len = strnlen(s, MAX_STRING_LEN);
    if (len >= MAX_STRING_LEN) {
        return NULL;
    }

    if (len > SIZE_MAX - 1) {
        return NULL;
    }

    alloc_size = len + 1;
    copy = malloc(alloc_size);
    if (copy == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        copy[i] = s[i];
    }
    copy[len] = '\0';
    return copy;
}

static int dict_add(Dict *d, const char *key, const char *value)
{
    char *k;
    char *v;

    if (d == NULL || key == NULL) {
        return -1;
    }

    if (d->count == d->capacity) {
        size_t new_capacity = (d->capacity == 0) ? 8 : d->capacity * 2;
        DictItem *tmp;

        if (new_capacity <= d->capacity) {
            return -1;
        }
        if (new_capacity > SIZE_MAX / sizeof(DictItem)) {
            return -1;
        }
        tmp = realloc(d->items, new_capacity * sizeof(DictItem));
        if (tmp == NULL) {
            return -1;
        }
        d->items = tmp;
        d->capacity = new_capacity;
    }

    k = duplicate_string(key);
    if (k == NULL) {
        return -1;
    }

    if (value != NULL) {
        v = duplicate_string(value);
        if (v == NULL) {
            free(k);
            return -1;
        }
    } else {
        v = NULL;
    }

    d->items[d->count].key = k;
    d->items[d->count].value = v;
    d->count++;
    return 0;
}

static void dict_drop_empty(Dict *d)
{
    size_t i;
    size_t write_index = 0;

    if (d == NULL) {
        return;
    }

    for (i = 0; i < d->count; i++) {
        if (d->items[i].value == NULL || d->items[i].value[0] == '\0') {
            free(d->items[i].key);
            free(d->items[i].value);
        } else {
            d->items[write_index] = d->items[i];
            write_index++;
        }
    }
    d->count = write_index;
}

static void dict_print(const Dict *d)
{
    size_t i;

    if (d == NULL) {
        return;
    }

    printf("{");
    for (i = 0; i < d->count; i++) {
        printf("\"%s\": \"%s\"",
               (d->items[i].key != NULL) ? d->items[i].key : "",
               (d->items[i].value != NULL) ? d->items[i].value : "");
        if (i + 1 < d->count) {
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
    for (i = 0; i < d->count; i++) {
        free(d->items[i].key);
        free(d->items[i].value);
    }
    free(d->items);
    free(d);
}

int main(void)
{
    Dict *d = dict_create();

    if (d == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if (dict_add(d, "c1", "Red") != 0 ||
        dict_add(d, "c2", "Green") != 0 ||
        dict_add(d, "c3", "") != 0 ||
        dict_add(d, "c4", NULL) != 0 ||
        dict_add(d, "c5", "Blue") != 0) {
        fprintf(stderr, "Failed to add items\n");
        dict_destroy(d);
        return EXIT_FAILURE;
    }

    printf("Before: ");
    dict_print(d);

    dict_drop_empty(d);

    printf("After:  ");
    dict_print(d);

    dict_destroy(d);
    return EXIT_SUCCESS;
}