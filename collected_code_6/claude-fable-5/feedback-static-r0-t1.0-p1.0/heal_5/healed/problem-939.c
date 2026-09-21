#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAIRS 16
#define MAX_STR_LEN 4096

typedef struct {
    char *key;
    char *value;
} Pair;

typedef struct {
    Pair pairs[MAX_PAIRS];
    size_t count;
} Dict;

static char *dup_string(const char *src)
{
    size_t len;
    size_t alloc_size;
    char *copy;

    if (src == NULL) {
        return NULL;
    }
    len = strnlen(src, MAX_STR_LEN);
    if (len >= MAX_STR_LEN) {
        return NULL;
    }
    alloc_size = len + 1U;
    copy = malloc(alloc_size);
    if (copy == NULL) {
        return NULL;
    }
    if (len >= alloc_size) {
        free(copy);
        return NULL;
    }
    memcpy(copy, src, len);
    copy[len] = '\0';
    return copy;
}

static int dict_set(Dict *d, const char *key, const char *value)
{
    char *k;
    char *v;

    if (d == NULL || key == NULL || value == NULL) {
        return -1;
    }
    if (d->count >= MAX_PAIRS) {
        return -1;
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
    d->pairs[d->count].key = k;
    d->pairs[d->count].value = v;
    d->count++;
    return 0;
}

static const char *dict_get(const Dict *d, const char *key)
{
    size_t i;

    if (d == NULL || key == NULL) {
        return NULL;
    }
    for (i = 0; i < d->count; i++) {
        if (d->pairs[i].key != NULL && strcmp(d->pairs[i].key, key) == 0) {
            return d->pairs[i].value;
        }
    }
    return NULL;
}

static void dict_free(Dict *d)
{
    size_t i;

    if (d == NULL) {
        return;
    }
    for (i = 0; i < d->count; i++) {
        free(d->pairs[i].key);
        free(d->pairs[i].value);
        d->pairs[i].key = NULL;
        d->pairs[i].value = NULL;
    }
    d->count = 0;
}

static const char *g_sort_key = NULL;

static int compare_dicts(const void *a, const void *b)
{
    const Dict *da = a;
    const Dict *db = b;
    const char *va = dict_get(da, g_sort_key);
    const char *vb = dict_get(db, g_sort_key);

    if (va == NULL && vb == NULL) {
        return 0;
    }
    if (va == NULL) {
        return -1;
    }
    if (vb == NULL) {
        return 1;
    }
    return strcmp(va, vb);
}

static int sort_dict_list(Dict *list, size_t count, const char *key)
{
    if (list == NULL || key == NULL) {
        return -1;
    }
    if (count < 2U) {
        return 0;
    }
    g_sort_key = key;
    qsort(list, count, sizeof(Dict), compare_dicts);
    g_sort_key = NULL;
    return 0;
}

static void print_dict_list(const Dict *list, size_t count)
{
    size_t i;
    size_t j;

    if (list == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        printf("{ ");
        for (j = 0; j < list[i].count; j++) {
            printf("%s: %s", list[i].pairs[j].key, list[i].pairs[j].value);
            if (j + 1U < list[i].count) {
                printf(", ");
            }
        }
        printf(" }\n");
    }
}

int main(void)
{
    Dict list[3];
    size_t i;
    int status = EXIT_SUCCESS;

    memset(list, 0, sizeof(list));

    if (dict_set(&list[0], "name", "Charlie") != 0 ||
        dict_set(&list[0], "age", "35") != 0 ||
        dict_set(&list[1], "name", "Alice") != 0 ||
        dict_set(&list[1], "age", "30") != 0 ||
        dict_set(&list[2], "name", "Bob") != 0 ||
        dict_set(&list[2], "age", "25") != 0) {
        fprintf(stderr, "Failed to build dictionaries\n");
        status = EXIT_FAILURE;
        goto cleanup;
    }

    printf("Before sorting:\n");
    print_dict_list(list, 3);

    if (sort_dict_list(list, 3, "name") != 0) {
        fprintf(stderr, "Sort failed\n");
        status = EXIT_FAILURE;
        goto cleanup;
    }

    printf("\nAfter sorting by name:\n");
    print_dict_list(list, 3);

cleanup:
    for (i = 0; i < 3U; i++) {
        dict_free(&list[i]);
    }
    return status;
}