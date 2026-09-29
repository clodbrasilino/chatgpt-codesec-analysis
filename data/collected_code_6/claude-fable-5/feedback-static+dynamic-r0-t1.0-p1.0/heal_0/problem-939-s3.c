#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAIRS 16
#define MAX_KEY_LEN 32
#define MAX_VAL_LEN 64

typedef struct {
    char key[MAX_KEY_LEN];
    char value[MAX_VAL_LEN];
} Pair;

typedef struct {
    Pair pairs[MAX_PAIRS];
    size_t count;
} Dict;

static int dict_add(Dict *d, const char *key, const char *value)
{
    if (d == NULL || key == NULL || value == NULL) {
        return -1;
    }
    if (d->count >= MAX_PAIRS) {
        return -1;
    }
    if (strlen(key) >= MAX_KEY_LEN || strlen(value) >= MAX_VAL_LEN) {
        return -1;
    }
    strncpy(d->pairs[d->count].key, key, MAX_KEY_LEN - 1);
    d->pairs[d->count].key[MAX_KEY_LEN - 1] = '\0';
    strncpy(d->pairs[d->count].value, value, MAX_VAL_LEN - 1);
    d->pairs[d->count].value[MAX_VAL_LEN - 1] = '\0';
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
        if (strcmp(d->pairs[i].key, key) == 0) {
            return d->pairs[i].value;
        }
    }
    return NULL;
}

static const char *g_sort_key = NULL;

static int compare_dicts(const void *a, const void *b)
{
    const Dict *da = (const Dict *)a;
    const Dict *db = (const Dict *)b;
    const char *va;
    const char *vb;

    va = dict_get(da, g_sort_key);
    vb = dict_get(db, g_sort_key);

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

static int sort_dict_list(Dict *list, size_t n, const char *key)
{
    if (list == NULL || key == NULL || n == 0) {
        return -1;
    }
    g_sort_key = key;
    qsort(list, n, sizeof(Dict), compare_dicts);
    g_sort_key = NULL;
    return 0;
}

static void print_dict_list(const Dict *list, size_t n)
{
    size_t i;
    size_t j;

    if (list == NULL) {
        return;
    }
    for (i = 0; i < n; i++) {
        printf("{");
        for (j = 0; j < list[i].count; j++) {
            printf("\"%s\": \"%s\"", list[i].pairs[j].key, list[i].pairs[j].value);
            if (j + 1 < list[i].count) {
                printf(", ");
            }
        }
        printf("}\n");
    }
}

int main(void)
{
    Dict *list;
    size_t n = 3;

    list = calloc(n, sizeof(Dict));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (dict_add(&list[0], "name", "Charlie") != 0 ||
        dict_add(&list[0], "age", "35") != 0 ||
        dict_add(&list[1], "name", "Alice") != 0 ||
        dict_add(&list[1], "age", "30") != 0 ||
        dict_add(&list[2], "name", "Bob") != 0 ||
        dict_add(&list[2], "age", "25") != 0) {
        fprintf(stderr, "Failed to populate dictionaries\n");
        free(list);
        return EXIT_FAILURE;
    }

    printf("Before sorting:\n");
    print_dict_list(list, n);

    if (sort_dict_list(list, n, "name") != 0) {
        fprintf(stderr, "Sort failed\n");
        free(list);
        return EXIT_FAILURE;
    }

    printf("After sorting by name:\n");
    print_dict_list(list, n);

    free(list);
    return EXIT_SUCCESS;
}