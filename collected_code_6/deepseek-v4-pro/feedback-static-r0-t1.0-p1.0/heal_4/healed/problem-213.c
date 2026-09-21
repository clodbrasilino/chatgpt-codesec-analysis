#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} StringTuple;

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
            size_t j;
            for (j = 0; j < i; j++) {
                free(result.items[j]);
            }
            free(result.items);
            result.items = NULL;
            result.count = 0;
            return result;
        }

        result.items[i] = (char *)malloc(len + 1);
        if (result.items[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(result.items[j]);
            }
            free(result.items);
            result.items = NULL;
            result.count = 0;
            return result;
        }
        memcpy(result.items[i], a->items[i], len);
        result.items[i][len] = '\0';
    }

    for (i = 0; i < b->count; i++) {
        if (b->items[i] == NULL) {
            result.items[a->count + i] = NULL;
            continue;
        }

        size_t len = strnlen(b->items[i], SIZE_MAX);
        if (len == SIZE_MAX) {
            size_t j;
            for (j = 0; j < a->count + i; j++) {
                free(result.items[j]);
            }
            free(result.items);
            result.items = NULL;
            result.count = 0;
            return result;
        }

        result.items[a->count + i] = (char *)malloc(len + 1);
        if (result.items[a->count + i] == NULL) {
            size_t j;
            for (j = 0; j < a->count + i; j++) {
                free(result.items[j]);
            }
            free(result.items);
            result.items = NULL;
            result.count = 0;
            return result;
        }
        memcpy(result.items[a->count + i], b->items[i], len);
        result.items[a->count + i][len] = '\0';
    }

    return result;
}

void tuple_free(StringTuple *tuple) {
    if (tuple != NULL && tuple->items != NULL) {
        size_t i;
        for (i = 0; i < tuple->count; i++) {
            free(tuple->items[i]);
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