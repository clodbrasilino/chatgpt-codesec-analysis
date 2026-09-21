#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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

        size_t len = strlen(a->items[i]);
        size_t alloc_size = len + 1;

        if (alloc_size < len) {
            cleanup_partial(&result, i);
            return result;
        }

        result.items[i] = (char *)malloc(alloc_size);
        if (result.items[i] == NULL) {
            cleanup_partial(&result, i);
            return result;
        }

        memcpy(result.items[i], a->items[i], alloc_size);
    }

    for (i = 0; i < b->count; i++) {
        size_t idx = a->count + i;

        if (b->items[i] == NULL) {
            result.items[idx] = NULL;
            continue;
        }

        size_t len = strlen(b->items[i]);
        size_t alloc_size = len + 1;

        if (alloc_size < len) {
            cleanup_partial(&result, idx);
            return result;
        }

        result.items[idx] = (char *)malloc(alloc_size);
        if (result.items[idx] == NULL) {
            cleanup_partial(&result, idx);
            return result;
        }

        memcpy(result.items[idx], b->items[i], alloc_size);
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