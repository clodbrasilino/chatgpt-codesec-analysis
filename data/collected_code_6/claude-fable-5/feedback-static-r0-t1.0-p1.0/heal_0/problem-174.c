#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char **values;
    size_t count;
    size_t capacity;
} Entry;

typedef struct {
    Entry *entries;
    size_t count;
    size_t capacity;
} Dict;

static char *dup_string(const char *s)
{
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }
    len = strlen(s) + 1U;
    copy = malloc(len);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, s, len);
    return copy;
}

static int dict_init(Dict *d)
{
    if (d == NULL) {
        return -1;
    }
    d->entries = NULL;
    d->count = 0U;
    d->capacity = 0U;
    return 0;
}

static Entry *dict_find(Dict *d, const char *key)
{
    size_t i;

    if (d == NULL || key == NULL) {
        return NULL;
    }
    for (i = 0U; i < d->count; i++) {
        if (strcmp(d->entries[i].key, key) == 0) {
            return &d->entries[i];
        }
    }
    return NULL;
}

static int entry_add_value(Entry *e, const char *value)
{
    char *copy;

    if (e == NULL || value == NULL) {
        return -1;
    }
    if (e->count == e->capacity) {
        size_t new_cap = (e->capacity == 0U) ? 4U : e->capacity * 2U;
        char **tmp;

        if (new_cap > SIZE_MAX / sizeof(char *)) {
            return -1;
        }
        tmp = realloc(e->values, new_cap * sizeof(char *));
        if (tmp == NULL) {
            return -1;
        }
        e->values = tmp;
        e->capacity = new_cap;
    }
    copy = dup_string(value);
    if (copy == NULL) {
        return -1;
    }
    e->values[e->count] = copy;
    e->count++;
    return 0;
}

static int dict_add(Dict *d, const char *key, const char *value)
{
    Entry *e;

    if (d == NULL || key == NULL || value == NULL) {
        return -1;
    }
    e = dict_find(d, key);
    if (e == NULL) {
        if (d->count == d->capacity) {
            size_t new_cap = (d->capacity == 0U) ? 4U : d->capacity * 2U;
            Entry *tmp;

            if (new_cap > SIZE_MAX / sizeof(Entry)) {
                return -1;
            }
            tmp = realloc(d->entries, new_cap * sizeof(Entry));
            if (tmp == NULL) {
                return -1;
            }
            d->entries = tmp;
            d->capacity = new_cap;
        }
        e = &d->entries[d->count];
        e->key = dup_string(key);
        if (e->key == NULL) {
            return -1;
        }
        e->values = NULL;
        e->count = 0U;
        e->capacity = 0U;
        d->count++;
    }
    return entry_add_value(e, value);
}

static void dict_free(Dict *d)
{
    size_t i;
    size_t j;

    if (d == NULL) {
        return;
    }
    for (i = 0U; i < d->count; i++) {
        for (j = 0U; j < d->entries[i].count; j++) {
            free(d->entries[i].values[j]);
        }
        free(d->entries[i].values);
        free(d->entries[i].key);
    }
    free(d->entries);
    d->entries = NULL;
    d->count = 0U;
    d->capacity = 0U;
}

static void dict_print(const Dict *d)
{
    size_t i;
    size_t j;

    if (d == NULL) {
        return;
    }
    for (i = 0U; i < d->count; i++) {
        printf("%s: [", d->entries[i].key);
        for (j = 0U; j < d->entries[i].count; j++) {
            printf("%s%s", d->entries[i].values[j],
                   (j + 1U < d->entries[i].count) ? ", " : "");
        }
        printf("]\n");
    }
}

int main(void)
{
    Dict d;
    size_t i;
    static const char *pairs[][2] = {
        {"fruit", "apple"},
        {"vegetable", "carrot"},
        {"fruit", "banana"},
        {"fruit", "cherry"},
        {"vegetable", "potato"},
        {"grain", "rice"}
    };
    size_t n = sizeof(pairs) / sizeof(pairs[0]);

    if (dict_init(&d) != 0) {
        fprintf(stderr, "Initialization failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < n; i++) {
        if (dict_add(&d, pairs[i][0], pairs[i][1]) != 0) {
            fprintf(stderr, "Failed to add pair\n");
            dict_free(&d);
            return EXIT_FAILURE;
        }
    }

    dict_print(&d);
    dict_free(&d);
    return EXIT_SUCCESS;
}