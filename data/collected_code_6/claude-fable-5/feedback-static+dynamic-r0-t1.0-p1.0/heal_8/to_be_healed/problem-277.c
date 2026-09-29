#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LEN 4096

typedef struct {
    char *key;
    int value;
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
    if (capacity > (size_t)-1 / sizeof(DictEntry)) {
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

static int dict_grow(Dict *d)
{
    DictEntry *tmp;
    size_t new_capacity;

    if (d->capacity > (size_t)-1 / (2 * sizeof(DictEntry))) {
        return -1;
    }
    new_capacity = d->capacity * 2;
    tmp = realloc(d->entries, new_capacity * sizeof(DictEntry));
    if (tmp == NULL) {
        return -1;
    }
    d->entries = tmp;
    d->capacity = new_capacity;
    return 0;
}

static char *dict_copy_key(const char *key)
{
    char *key_copy;
    size_t key_len;

    key_len = strnlen(key, MAX_KEY_LEN);
    if (key_len >= MAX_KEY_LEN) {
        return NULL;
    }
    key_copy = malloc(key_len + 1);
    if (key_copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(key_copy, key, key_len);
    key_copy[key_len] = '\0';
    return key_copy;
}

static int dict_add(Dict *d, const char *key, int value)
{
    char *key_copy;

    if (d == NULL || key == NULL) {
        return -1;
    }
    if (d->size >= d->capacity) {
        if (dict_grow(d) != 0) {
            return -1;
        }
    }
    key_copy = dict_copy_key(key);
    if (key_copy == NULL) {
        return -1;
    }
    d->entries[d->size].key = key_copy;
    d->entries[d->size].value = value;
    d->size++;
    return 0;
}

static void dict_destroy(Dict *d)
{
    size_t i;

    if (d == NULL) {
        return;
    }
    for (i = 0; i < d->size; i++) {
        free(d->entries[i].key);
    }
    free(d->entries);
    free(d);
}

static Dict *dict_filter(const Dict *d, int (*predicate)(int))
{
    Dict *result;
    size_t i;

    if (d == NULL || predicate == NULL) {
        return NULL;
    }
    result = dict_create(d->capacity);
    if (result == NULL) {
        return NULL;
    }
    for (i = 0; i < d->size; i++) {
        if (predicate(d->entries[i].value)) {
            if (dict_add(result, d->entries[i].key, d->entries[i].value) != 0) {
                dict_destroy(result);
                return NULL;
            }
        }
    }
    return result;
}

static int value_greater_than_ten(int value)
{
    return value > 10;
}

static void dict_print(const Dict *d)
{
    size_t i;

    if (d == NULL) {
        return;
    }
    for (i = 0; i < d->size; i++) {
        printf("%s: %d\n", d->entries[i].key, d->entries[i].value);
    }
}

int main(void)
{
    Dict *d;
    Dict *filtered;

    d = dict_create(4);
    if (d == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }
    if (dict_add(d, "apple", 5) != 0 ||
        dict_add(d, "banana", 15) != 0 ||
        dict_add(d, "cherry", 25) != 0 ||
        dict_add(d, "date", 8) != 0 ||
        dict_add(d, "elderberry", 30) != 0) {
        fprintf(stderr, "Failed to add entries\n");
        dict_destroy(d);
        return EXIT_FAILURE;
    }

    printf("Original dictionary:\n");
    dict_print(d);

    filtered = dict_filter(d, value_greater_than_ten);
    if (filtered == NULL) {
        fprintf(stderr, "Failed to filter dictionary\n");
        dict_destroy(d);
        return EXIT_FAILURE;
    }

    printf("\nFiltered dictionary (values > 10):\n");
    dict_print(filtered);

    dict_destroy(filtered);
    dict_destroy(d);
    return EXIT_SUCCESS;
}