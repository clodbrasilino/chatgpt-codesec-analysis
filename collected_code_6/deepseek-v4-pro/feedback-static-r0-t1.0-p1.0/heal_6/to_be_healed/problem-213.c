#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} StringTuple;

static void cleanup_partial(StringTuple *result, size_t limit) {
    size_t j;
    for (j = 0; j < limit; j++) {
        free(result->items[j]);
        result->items[j] = NULL;
    }
    free(result->items);
    result->items = NULL;
    result->count = 0;
}

StringTuple tuple_concat(const StringTuple *a, const StringTuple *b) {
    StringTuple result;
    size_t i;

    if (a == NULL || b == NULL || a->items == NULL || b->items == NULL) {
        result.items = NULL;
        result.count = 0;
        return result;
    }

    if (a->count > SIZE_MAX - b->count) {
        result.items = NULL;
        result.count = 0;
        return result;
    }

    result.count = a->count + b->count;
    result.items = (char **)calloc(result.count, sizeof(char *));
    if (result.items == NULL) {
        result.count = 0;
        return result;
    }

    for (i = 0; i < a->count; i++) {
        if (a->items[i] == NULL) {
            result.items[i] = NULL;
            continue;
        }

        size_t len = strnlen(a->items[i], SIZE_MAX);
        if (len == SIZE_MAX) {
            cleanup_partial(&result, i);
            return result;
        }

        result.items[i] = (char *)malloc(len + 1);
        if (result.items[i] == NULL) {
            cleanup_partial(&result, i);
            return result;
        }

        if (len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result.items[i], a->items[i], len);
        }
        result.items[i][len] = '\0';
    }

    for (i = 0; i < b->count; i++) {
        size_t idx = a->count + i;

        if (b->items[i] == NULL) {
            result.items[idx] = NULL;
            continue;
        }

        size_t len = strnlen(b->items[i], SIZE_MAX);
        if (len == SIZE_MAX) {
            cleanup_partial(&result, idx);
            return result;
        }

        result.items[idx] = (char *)malloc(len + 1);
        if (result.items[idx] == NULL) {
            cleanup_partial(&result, idx);
            return result;
        }

        if (len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result.items[idx], b->items[i], len);
        }
        result.items[idx][len] = '\0';
    }

    return result;
}

void tuple_free(StringTuple *tuple) {
    if (tuple != NULL && tuple->items != NULL) {
        size_t i;
        for (i = 0; i < tuple->count; i++) {
            free(tuple->items[i]);
            tuple->items[i] = NULL;
        }
        free(tuple->items);
        tuple->items = NULL;
    }
    if (tuple != NULL) {
        tuple->count = 0;
    }
}

int main(void) {
    char *items_a[] = {"hello", "world"};
    char *items_b[] = {"foo", "bar", "baz"};
    StringTuple a = {items_a, 2};
    StringTuple b = {items_b, 3};
    StringTuple result;
    size_t i;

    result = tuple_concat(&a, &b);

    if (result.items == NULL) {
        fprintf(stderr, "Failed to concatenate tuples\n");
        return 1;
    }

    for (i = 0; i < result.count; i++) {
        if (result.items[i] != NULL) {
            printf("%s\n", result.items[i]);
        } else {
            printf("(null)\n");
        }
    }

    tuple_free(&result);

    return 0;
}