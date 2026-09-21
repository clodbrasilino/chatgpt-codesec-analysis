#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LEN 4096U

typedef struct {
    char *key;
    char *value;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dict;

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t i;

    for (i = 0U; i < max_len; i++) {
        if (s[i] == '\0') {
            return i;
        }
    }
    return max_len;
}

static char *dup_string(const char *s)
{
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }
    len = bounded_strlen(s, MAX_STRING_LEN);
    if (len >= MAX_STRING_LEN) {
        return NULL;
    }
    copy = malloc(len + 1U);
    if (copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, s, len);
    copy[len] = '\0';
    return copy;
}

Dict *dict_create(void)
{
    Dict *d = malloc(sizeof(Dict));

    if (d == NULL) {
        return NULL;
    }
    d->size = 0U;
    d->capacity = 8U;
    if (d->capacity > (SIZE_MAX / sizeof(Entry))) {
        free(d);
        return NULL;
    }
    d->entries = malloc(d->capacity * sizeof(Entry));
    if (d->entries == NULL) {
        free(d);
        return NULL;
    }
    return d;
}

void dict_free(Dict *d)
{
    size_t i;

    if (d == NULL) {
        return;
    }
    for (i = 0U; i < d->size; i++) {
        free(d->entries[i].key);
        free(d->entries[i].value);
    }
    free(d->entries);
    free(d);
}

static Entry *dict_find(const Dict *d, const char *key)
{
    size_t i;

    for (i = 0U; i < d->size; i++) {
        if (strcmp(d->entries[i].key, key) == 0) {
            return &d->entries[i];
        }
    }
    return NULL;
}

int dict_set(Dict *d, const char *key, const char *value)
{
    Entry *found;
    char *new_key;
    char *new_value;

    if ((d == NULL) || (key == NULL) || (value == NULL)) {
        return -1;
    }
    found = dict_find(d, key);
    if (found != NULL) {
        new_value = dup_string(value);
        if (new_value == NULL) {
            return -1;
        }
        free(found->value);
        found->value = new_value;
        return 0;
    }
    if (d->size == d->capacity) {
        size_t new_capacity = d->capacity * 2U;
        Entry *tmp;

        if (new_capacity <= d->capacity) {
            return -1;
        }
        if (new_capacity > (SIZE_MAX / sizeof(Entry))) {
            return -1;
        }
        tmp = realloc(d->entries, new_capacity * sizeof(Entry));
        if (tmp == NULL) {
            return -1;
        }
        d->entries = tmp;
        d->capacity = new_capacity;
    }
    new_key = dup_string(key);
    if (new_key == NULL) {
        return -1;
    }
    new_value = dup_string(value);
    if (new_value == NULL) {
        free(new_key);
        return -1;
    }
    d->entries[d->size].key = new_key;
    d->entries[d->size].value = new_value;
    d->size++;
    return 0;
}

static int dict_copy_into(Dict *dest, const Dict *src)
{
    size_t i;

    for (i = 0U; i < src->size; i++) {
        if (dict_set(dest, src->entries[i].key, src->entries[i].value) != 0) {
            return -1;
        }
    }
    return 0;
}

Dict *merge_three_dicts(const Dict *a, const Dict *b, const Dict *c)
{
    Dict *merged;

    if ((a == NULL) || (b == NULL) || (c == NULL)) {
        return NULL;
    }
    merged = dict_create();
    if (merged == NULL) {
        return NULL;
    }
    if ((dict_copy_into(merged, a) != 0) ||
        (dict_copy_into(merged, b) != 0) ||
        (dict_copy_into(merged, c) != 0)) {
        dict_free(merged);
        return NULL;
    }
    return merged;
}

void dict_print(const Dict *d)
{
    size_t i;

    if (d == NULL) {
        return;
    }
    printf("{");
    for (i = 0U; i < d->size; i++) {
        printf("\"%s\": \"%s\"", d->entries[i].key, d->entries[i].value);
        if (i + 1U < d->size) {
            printf(", ");
        }
    }
    printf("}\n");
}

int main(void)
{
    Dict *a;
    Dict *b;
    Dict *c;
    int status = EXIT_FAILURE;

    a = dict_create();
    b = dict_create();
    c = dict_create();
    if ((a == NULL) || (b == NULL) || (c == NULL)) {
        dict_free(a);
        dict_free(b);
        dict_free(c);
        fprintf(stderr, "allocation failure\n");
        return EXIT_FAILURE;
    }
    if ((dict_set(a, "apple", "1") == 0) &&
        (dict_set(a, "banana", "2") == 0) &&
        (dict_set(b, "cherry", "3") == 0) &&
        (dict_set(b, "banana", "20") == 0) &&
        (dict_set(c, "date", "4") == 0) &&
        (dict_set(c, "apple", "10") == 0)) {
        Dict *merged = merge_three_dicts(a, b, c);

        if (merged != NULL) {
            printf("Dict A: ");
            dict_print(a);
            printf("Dict B: ");
            dict_print(b);
            printf("Dict C: ");
            dict_print(c);
            printf("Merged: ");
            dict_print(merged);
            dict_free(merged);
            status = EXIT_SUCCESS;
        } else {
            fprintf(stderr, "merge failure\n");
        }
    } else {
        fprintf(stderr, "insertion failure\n");
    }
    dict_free(a);
    dict_free(b);
    dict_free(c);
    return status;
}