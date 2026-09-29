#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
} TupleList;

static void free_tuple_list(TupleList *list) {
    if (list == NULL) {
        return;
    }

    if (list->items != NULL) {
        for (size_t i = 0; i < list->count; i++) {
            free(list->items[i].data);
        }
        free(list->items);
    }

    list->items = NULL;
    list->count = 0;
}

static TupleList trim_tuples(const TupleList *list, size_t k) {
    TupleList result = {0};

    if (list == NULL || list->items == NULL || list->count == 0) {
        return result;
    }

    result.items = calloc(list->count, sizeof(*result.items));
    if (result.items == NULL) {
        return result;
    }
    result.count = list->count;

    for (size_t i = 0; i < list->count; i++) {
        size_t old_size = list->items[i].size;
        size_t half = old_size / 2 + old_size % 2;

        if (k >= half) {
            result.items[i].data = NULL;
            result.items[i].size = 0;
            continue;
        }

        size_t new_size = old_size - 2 * k;
        result.items[i].data = malloc(new_size * sizeof(int));
        if (result.items[i].data == NULL) {
            free_tuple_list(&result);
            return result;
        }

        for (size_t j = 0; j < new_size; j++) {
            result.items[i].data[j] = list->items[i].data[j + k];
        }

        result.items[i].size = new_size;
    }

    return result;
}

int main(void) {
    TupleList input = {0};
    const size_t sizes[] = {5, 4, 2};
    int values[][5] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9},
        {10, 11}
    };

    input.count = 3;
    input.items = calloc(input.count, sizeof(*input.items));
    if (input.items == NULL) {
        return 1;
    }

    for (size_t i = 0; i < input.count; i++) {
        input.items[i].size = sizes[i];
        input.items[i].data = malloc(sizes[i] * sizeof(int));
        if (input.items[i].data == NULL) {
            free_tuple_list(&input);
            return 1;
        }

        for (size_t j = 0; j < sizes[i]; j++) {
            input.items[i].data[j] = values[i][j];
        }
    }

    TupleList trimmed = trim_tuples(&input, 1);
    if (trimmed.items == NULL && input.count > 0) {
        free_tuple_list(&input);
        return 1;
    }

    for (size_t i = 0; i < trimmed.count; i++) {
        printf("(");
        for (size_t j = 0; j < trimmed.items[i].size; j++) {
            printf("%d", trimmed.items[i].data[j]);
            if (j + 1 < trimmed.items[i].size) {
                printf(", ");
            }
        }
        printf(")\n");
    }

    free_tuple_list(&trimmed);
    free_tuple_list(&input);

    return 0;
}