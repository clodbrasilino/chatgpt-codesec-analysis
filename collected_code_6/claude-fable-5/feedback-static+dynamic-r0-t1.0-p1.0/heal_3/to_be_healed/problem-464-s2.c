#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_KEY_LEN 64

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_LEN];
    int value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dict;

static Dict *dict_create(size_t capacity)
{
    Dict *d = NULL;

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

static void dict_destroy(Dict *d)
{
    if (d != NULL) {
        free(d->entries);
        d->entries = NULL;
        free(d);
    }
}

static bool dict_add(Dict *d, const char *key, int value)
{
    size_t key_len;

    if (d == NULL || key == NULL) {
        return false;
    }

    if (d->size >= d->capacity) {
        return false;
    }

    key_len = strnlen(key, MAX_KEY_LEN);
    if (key_len >= MAX_KEY_LEN) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(d->entries[d->size].key, key, key_len);
    d->entries[d->size].key[key_len] = '\0';
    d->entries[d->size].value = value;
    d->size++;
    return true;
}

static bool all_values_same(const Dict *d, bool *result)
{
    size_t i;

    if (d == NULL || result == NULL) {
        return false;
    }

    if (d->size == 0) {
        *result = true;
        return true;
    }

    *result = true;
    for (i = 1; i < d->size; i++) {
        if (d->entries[i].value != d->entries[0].value) {
            *result = false;
            break;
        }
    }
    return true;
}

int main(void)
{
    Dict *d1 = NULL;
    Dict *d2 = NULL;
    bool result = false;

    d1 = dict_create(4);
    if (d1 == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if (!dict_add(d1, "a", 10) || !dict_add(d1, "b", 10) || !dict_add(d1, "c", 10)) {
        fprintf(stderr, "Failed to add entries\n");
        dict_destroy(d1);
        return EXIT_FAILURE;
    }

    if (!all_values_same(d1, &result)) {
        fprintf(stderr, "Check failed\n");
        dict_destroy(d1);
        return EXIT_FAILURE;
    }
    printf("Dict 1: all values same = %s\n", result ? "true" : "false");

    d2 = dict_create(4);
    if (d2 == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        dict_destroy(d1);
        return EXIT_FAILURE;
    }

    if (!dict_add(d2, "x", 1) || !dict_add(d2, "y", 2) || !dict_add(d2, "z", 1)) {
        fprintf(stderr, "Failed to add entries\n");
        dict_destroy(d1);
        dict_destroy(d2);
        return EXIT_FAILURE;
    }

    if (!all_values_same(d2, &result)) {
        fprintf(stderr, "Check failed\n");
        dict_destroy(d1);
        dict_destroy(d2);
        return EXIT_FAILURE;
    }
    printf("Dict 2: all values same = %s\n", result ? "true" : "false");

    dict_destroy(d1);
    dict_destroy(d2);
    return EXIT_SUCCESS;
}