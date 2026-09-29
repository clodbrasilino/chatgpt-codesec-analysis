#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAIRS 16
#define MAX_KEY_LEN 32
#define MAX_VAL_LEN 64

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char value[MAX_VAL_LEN];
} Pair;

typedef struct {
    Pair pairs[MAX_PAIRS];
    size_t count;
} Dict;

static size_t safe_strnlen(const char *s, size_t maxlen)
{
    size_t i;

    for (i = 0; i < maxlen; i++) {
        if (s[i] == '\0') {
            break;
        }
    }
    return i;
}

static int dict_add(Dict *d, const char *key, const char *value)
{
    size_t key_len;
    size_t val_len;
    Pair *p;

    if (d == NULL || key == NULL || value == NULL) {
        return -1;
    }
    if (d->count >= MAX_PAIRS) {
        return -1;
    }

    key_len = safe_strnlen(key, MAX_KEY_LEN);
    val_len = safe_strnlen(value, MAX_VAL_LEN);

    if (key_len >= MAX_KEY_LEN || val_len >= MAX_VAL_LEN) {
        return -1;
    }

    p = &d->pairs[d->count];

    if (key_len > sizeof(p->key) - 1 || val_len > sizeof(p->value) - 1) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(p->key, key, key_len);
    p->key[key_len] = '\0';

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(p->value, value, val_len);
    p->value[val_len] = '\0';

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
        if (strncmp(d->pairs[i].key, key, MAX_KEY_LEN) == 0) {
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
    return strncmp(va, vb, MAX_VAL_LEN);
}

static int sort_dict_list(Dict *list, size_t n, const char *key)
{
    if (list == NULL || key == NULL || n == 0) {
        return -1;
    }
    if (safe_strnlen(key, MAX_KEY_LEN) >= MAX_KEY_LEN) {
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
            printf("\"%.*s\": \"%.*s\"",
                   MAX_KEY_LEN, list[i].pairs[j].key,
                   MAX_VAL_LEN, list[i].pairs[j].value);
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