#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t length;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
} TupleList;

void free_tuple_list(TupleList *list) {
    size_t i;
    if (list == NULL) {
        return;
    }
    if (list->items != NULL) {
        for (i = 0; i < list->count; ++i) {
            free(list->items[i].elements);
        }
        free(list->items);
        list->items = NULL;
    }
    list->count = 0;
}

int extract_nth_element(const TupleList *list, size_t n, int *output) {
    size_t i;
    if (list == NULL || output == NULL || list->items == NULL || list->count == 0) {
        return -1;
    }
    for (i = 0; i < list->count; ++i) {
        if (list->items[i].elements == NULL || n >= list->items[i].length) {
            return -1;
        }
        output[i] = list->items[i].elements[n];
    }
    return 0;
}

int main(void) {
    TupleList list;
    int *result;
    size_t lengths[3] = {2, 3, 2};
    size_t i;
    size_t j;

    list.count = 3;
    list.items = calloc(list.count, sizeof(Tuple));
    if (list.items == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < list.count; ++i) {
        list.items[i].length = lengths[i];
        list.items[i].elements = malloc(lengths[i] * sizeof(int));
        if (list.items[i].elements == NULL) {
            free_tuple_list(&list);
            return EXIT_FAILURE;
        }
        for (j = 0; j < lengths[i]; ++j) {
            list.items[i].elements[j] = (int)(i * 10 + j);
        }
    }

    result = malloc(list.count * sizeof(int));
    if (result == NULL) {
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    if (extract_nth_element(&list, 1, result) != 0) {
        free(result);
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    for (i = 0; i < list.count; ++i) {
        printf("%d\n", result[i]);
    }

    free(result);
    free_tuple_list(&list);
    return EXIT_SUCCESS;
}