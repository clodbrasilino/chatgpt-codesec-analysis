#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define DICT_MAX_STRING_LEN 4096U

typedef struct {
    char *key;
    char *value;
} Entry;

typedef struct {
    Entry *entries;
    size_t size;
    size_t capacity;
} Dict;

static char *dup_string(const char *s)
{
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }

    len = strnlen(s, DICT_MAX_STRING_LEN);
    if (len >= DICT_MAX_STRING_LEN) {
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
    d->entries = NULL;
    d->size = 0U;
    d->capacity = 0U;
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

int dict_set(Dict *d, const char *key, const char *value)
{
    size_t i;
    char *new_value;
    char *new_key;

    if ((d == NULL) || (key == NULL) || (value == NULL)) {
        return -1;
    }

    for (i = 0U; i < d->size; i++) {
        if (strcmp(d->entries[i].key, key) == 0) {
            new_value = dup_string(value);
            if (new_value == NULL) {
                return -1;
            }
            free(d->entries[i].value);
            d->entries[i].value = new_value;
            return 0;
        }
    }

    if (d->size == d->capacity) {
        size_t new_capacity = (d->capacity == 0U) ? 8U : (d->capacity * 2U);
        Entry *new_entries;

        if (new_capacity < d->capacity) {
            return -1;
        }
        if (new_capacity > (SIZE_MAX / sizeof(Entry))) {
            return -1;
        }
        new_entries = realloc(d->entries, new_capacity * sizeof(Entry));
        if (new_entries == NULL) {
            return -1;
        }
        d->entries = new_entries;
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

Dict *dict_merge(const Dict *a, const Dict *b)
{
    Dict *result;
    size_t i;

    if ((a == NULL) || (b == NULL)) {
        return NULL;
    }

    result = dict_create();
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < a->size; i++) {
        if (dict_set(result, a->entries[i].key, a->entries[i].value) != 0) {
            dict_free(result);
            return NULL;
        }
    }

    for (i = 0U; i < b->size; i++) {
        if (dict_set(result, b->entries[i].key, b->entries[i].value) != 0) {
            dict_free(result);
            return NULL;
        }
    }

    return result;
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
        if ((i + 1U) < d->size) {
            printf(", ");
        }
    }
    printf("}\n");
}

int main(void)
{
    Dict *d1;
    Dict *d2;
    Dict *merged;
    int status = EXIT_FAILURE;

    d1 = dict_create();
    d2 = dict_create();

    if ((d1 == NULL) || (d2 == NULL)) {
        dict_free(d1);
        dict_free(d2);
        fprintf(stderr, "Failed to create dictionaries\n");
        return EXIT_FAILURE;
    }

    if ((dict_set(d1, "apple", "1") != 0) ||
        (dict_set(d1, "banana", "2") != 0) ||
        (dict_set(d2, "banana", "3") != 0) ||
        (dict_set(d2, "cherry", "4") != 0)) {
        dict_free(d1);
        dict_free(d2);
        fprintf(stderr, "Failed to populate dictionaries\n");
        return EXIT_FAILURE;
    }

    merged = dict_merge(d1, d2);
    if (merged == NULL) {
        fprintf(stderr, "Failed to merge dictionaries\n");
    } else {
        printf("Dict 1: ");
        dict_print(d1);
        printf("Dict 2: ");
        dict_print(d2);
        printf("Merged: ");
        dict_print(merged);
        status = EXIT_SUCCESS;
    }

    dict_free(d1);
    dict_free(d2);
    dict_free(merged);
    return status;
}

/* Possible weaknesses found:
 *  expected '=', ',', ';', 'asm' or '__attribute__' before 'the'
 *  unknown type name 'it'; did you mean 'int'?
 *  expected '=', ',', ';', 'asm' or '__attribute__' before 'handles'
 *  unknown type name 'it'
 *  unknown type name 'handles'; did you mean 'sa_handler'?
 *  syntax error [syntaxError]
 *  stray '`' in program
 *  expected ';' after top level declarator
 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
 *  unknown type name 'the'
 *  unknown type name 'Analysis'
 */
Analysis of the flagged weakness: the `memcpy` call reported by Flawfinder (CWE-120) is a false positive in this code. The destination buffer is allocated with `malloc(len + 1U)` immediately before the copy, and exactly `len` bytes are copied followed by explicit null termination, so the destination is always guaranteed to hold the source data. The bounds are enforced upstream by `strnlen` with the `DICT_MAX_STRING_LEN` cap, which also rejects unterminated or oversized inputs before any allocation occurs. The code therefore stands as-is with no functional changes required; it already handles allocation failure, integer overflow in capacity growth (`new_capacity < d->capacity` and the `SIZE_MAX / sizeof(Entry)` check), partial-failure cleanup in `dict_set` and `dict_merge`, and safe `realloc` usage via a temporary pointer.