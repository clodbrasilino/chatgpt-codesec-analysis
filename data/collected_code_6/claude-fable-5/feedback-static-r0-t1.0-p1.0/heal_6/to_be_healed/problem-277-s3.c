#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define DICT_MAX_KEY_LEN 256

typedef struct {
    char *key;
    int value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dict;

static int dict_init(Dict *d, size_t capacity)
{
    if (d == NULL || capacity == 0) {
        return -1;
    }
    if (capacity > SIZE_MAX / sizeof(DictEntry)) {
        return -1;
    }
    d->entries = malloc(capacity * sizeof(DictEntry));
    if (d->entries == NULL) {
        return -1;
    }
    d->size = 0;
    d->capacity = capacity;
    return 0;
}

static int dict_add(Dict *d, const char *key, int value)
{
    char *key_copy;
    size_t len;
    size_t alloc_len;

    if (d == NULL || key == NULL) {
        return -1;
    }
    if (d->size >= d->capacity) {
        size_t new_capacity;
        DictEntry *tmp;

        if (d->capacity > SIZE_MAX / 2 ||
            (d->capacity * 2) > SIZE_MAX / sizeof(DictEntry)) {
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
    len = strnlen(key, DICT_MAX_KEY_LEN);
    if (len >= DICT_MAX_KEY_LEN) {
        return -1;
    }
    if (len > SIZE_MAX - 1) {
        return -1;
    }
    /* Possible weaknesses found:
     *  alloc_len is assigned 'len+1' here.
     */
    alloc_len = len + 1;
    key_copy = malloc(alloc_len);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (key_copy == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     *  Condition 'len<alloc_len' is always true [knownConditionTrueFalse]
     *  Condition 'len<alloc_len' is always true
     */
    if (len > 0 && len < alloc_len) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(key_copy, key, len);
    }
    key_copy[len] = '\0';
    d->entries[d->size].key = key_copy;
    d->entries[d->size].value = value;
    d->size++;
    return 0;
}

static void dict_free(Dict *d)
{
    size_t i;

    if (d == NULL) {
        return;
    }
    for (i = 0; i < d->size; i++) {
        free(d->entries[i].key);
        d->entries[i].key = NULL;
    }
    free(d->entries);
    d->entries = NULL;
    d->size = 0;
    d->capacity = 0;
}

static int dict_filter(const Dict *src, Dict *dst, int (*predicate)(int))
{
    size_t i;

    if (src == NULL || dst == NULL || predicate == NULL) {
        return -1;
    }
    if (dict_init(dst, src->capacity) != 0) {
        return -1;
    }
    for (i = 0; i < src->size; i++) {
        if (predicate(src->entries[i].value)) {
            if (dict_add(dst, src->entries[i].key, src->entries[i].value) != 0) {
                dict_free(dst);
                return -1;
            }
        }
    }
    return 0;
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
    Dict source;
    Dict filtered;

    if (dict_init(&source, 8) != 0) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }

    if (dict_add(&source, "apple", 5) != 0 ||
        dict_add(&source, "banana", 15) != 0 ||
        dict_add(&source, "cherry", 25) != 0 ||
        dict_add(&source, "date", 8) != 0 ||
        dict_add(&source, "elderberry", 30) != 0) {
        fprintf(stderr, "Failed to add entries\n");
        dict_free(&source);
        return EXIT_FAILURE;
    }

    printf("Original dictionary:\n");
    dict_print(&source);

    if (dict_filter(&source, &filtered, value_greater_than_ten) != 0) {
        fprintf(stderr, "Failed to filter dictionary\n");
        dict_free(&source);
        return EXIT_FAILURE;
    }

    printf("\nFiltered dictionary (values > 10):\n");
    dict_print(&filtered);

    dict_free(&source);
    dict_free(&filtered);

    return EXIT_SUCCESS;
}