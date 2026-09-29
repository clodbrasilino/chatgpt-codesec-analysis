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

    result.count = a->count + b->count;
    result.items = (char **)malloc(result.count * sizeof(char *));
    if (result.items == NULL) {
        result.count = 0;
        return result;
    }

    for (i = 0; i < a->count; i++) {
        result.items[i] = (char *)malloc(strlen(a->items[i]) + 1);
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
        strcpy(result.items[i], a->items[i]);
    }

    for (i = 0; i < b->count; i++) {
        result.items[a->count + i] = (char *)malloc(strlen(b->items[i]) + 1);
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
        strcpy(result.items[a->count + i], b->items[i]);
    }

    return result;
}

void tuple_free(StringTuple *tuple) {
    size_t i;
    if (tuple->items != NULL) {
        for (i = 0; i < tuple->count; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
        tuple->items = NULL;
    }
    tuple->count = 0;
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
        printf("%s\n", result.items[i]);
    }

    tuple_free(&result);

    return 0;
}