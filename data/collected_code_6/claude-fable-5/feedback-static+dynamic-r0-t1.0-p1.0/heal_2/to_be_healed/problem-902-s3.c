#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DICT_MAX_KEY_LEN 256

typedef struct {
    char *key;
    int value;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dict;

static int dict_init(Dict *d, size_t capacity)
{
    if (d == NULL || capacity == 0) {
        return -1;
    }
    if (capacity > SIZE_MAX / sizeof(Entry)) {
        return -1;
    }
    d->entries = malloc(capacity * sizeof(Entry));
    if (d->entries == NULL) {
        return -1;
    }
    d->size = 0;
    d->capacity = capacity;
    return 0;
}

static void dict_free(Dict *d)
{
    if (d == NULL) {
        return;
    }
    for (size_t i = 0; i < d->size; i++) {
        free(d->entries[i].key);
        d->entries[i].key = NULL;
    }
    free(d->entries);
    d->entries = NULL;
    d->size = 0;
    d->capacity = 0;
}

static Entry *dict_find(Dict *d, const char *key)
{
    if (d == NULL || key == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < d->size; i++) {
        if (strncmp(d->entries[i].key, key, DICT_MAX_KEY_LEN) == 0) {
            return &d->entries[i];
        }
    }
    return NULL;
}

static int dict_add(Dict *d, const char *key, int value)
{
    if (d == NULL || key == NULL) {
        return -1;
    }
    size_t key_len = strnlen(key, DICT_MAX_KEY_LEN);
    if (key_len == DICT_MAX_KEY_LEN) {
        return -1;
    }
    Entry *existing = dict_find(d, key);
    if (existing != NULL) {
        existing->value += value;
        return 0;
    }
    if (d->size >= d->capacity) {
        size_t new_capacity = d->capacity * 2;
        if (new_capacity <= d->capacity ||
            new_capacity > SIZE_MAX / sizeof(Entry)) {
            return -1;
        }
        Entry *tmp = realloc(d->entries, new_capacity * sizeof(Entry));
        if (tmp == NULL) {
            return -1;
        }
        d->entries = tmp;
        d->capacity = new_capacity;
    }
    size_t alloc_len = key_len + 1;
    char *copy = malloc(alloc_len);
    if (copy == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, key, key_len);
    copy[key_len] = '\0';
    d->entries[d->size].key = copy;
    d->entries[d->size].value = value;
    d->size++;
    return 0;
}

static int dict_combine(Dict *dest, const Dict *a, const Dict *b)
{
    if (dest == NULL || a == NULL || b == NULL) {
        return -1;
    }
    for (size_t i = 0; i < a->size; i++) {
        if (dict_add(dest, a->entries[i].key, a->entries[i].value) != 0) {
            return -1;
        }
    }
    for (size_t i = 0; i < b->size; i++) {
        if (dict_add(dest, b->entries[i].key, b->entries[i].value) != 0) {
            return -1;
        }
    }
    return 0;
}

static void dict_print(const Dict *d)
{
    if (d == NULL) {
        return;
    }
    for (size_t i = 0; i < d->size; i++) {
        printf("%s: %d\n", d->entries[i].key, d->entries[i].value);
    }
}

int main(void)
{
    Dict a;
    Dict b;
    Dict combined;
    int status = EXIT_FAILURE;

    if (dict_init(&a, 4) != 0) {
        fprintf(stderr, "Failed to initialize dictionary a\n");
        return EXIT_FAILURE;
    }
    if (dict_init(&b, 4) != 0) {
        fprintf(stderr, "Failed to initialize dictionary b\n");
        dict_free(&a);
        return EXIT_FAILURE;
    }
    if (dict_init(&combined, 8) != 0) {
        fprintf(stderr, "Failed to initialize combined dictionary\n");
        dict_free(&a);
        dict_free(&b);
        return EXIT_FAILURE;
    }

    if (dict_add(&a, "apple", 3) != 0 ||
        dict_add(&a, "banana", 5) != 0 ||
        dict_add(&a, "cherry", 2) != 0) {
        fprintf(stderr, "Failed to populate dictionary a\n");
        goto cleanup;
    }

    if (dict_add(&b, "banana", 7) != 0 ||
        dict_add(&b, "cherry", 4) != 0 ||
        dict_add(&b, "date", 6) != 0) {
        fprintf(stderr, "Failed to populate dictionary b\n");
        goto cleanup;
    }

    if (dict_combine(&combined, &a, &b) != 0) {
        fprintf(stderr, "Failed to combine dictionaries\n");
        goto cleanup;
    }

    printf("Dictionary a:\n");
    dict_print(&a);
    printf("\nDictionary b:\n");
    dict_print(&b);
    printf("\nCombined dictionary:\n");
    dict_print(&combined);

    status = EXIT_SUCCESS;

cleanup:
    dict_free(&a);
    dict_free(&b);
    dict_free(&combined);
    return status;
}