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

int remove_tuples_of_length_k(TupleList *list, size_t k) {
    if (list == NULL) {
        return -1;
    }
    if (list->items == NULL) {
        return 0;
    }

    size_t write_idx = 0;
    for (size_t i = 0; i < list->count; i++) {
        if (list->items[i].length == k) {
            free(list->items[i].elements);
            list->items[i].elements = NULL;
        } else {
            if (write_idx != i) {
                list->items[write_idx] = list->items[i];
            }
            write_idx++;
        }
    }
    
    list->count = write_idx;

    if (list->count == 0) {
        free(list->items);
        list->items = NULL;
    } else {
        Tuple *temp = realloc(list->items, list->count * sizeof(Tuple));
        if (temp != NULL) {
            list->items = temp;
        }
    }

    return 0;
}

void free_tuple_list(TupleList *list) {
    if (list == NULL) {
        return;
    }
    if (list->items != NULL) {
        for (size_t i = 0; i < list->count; i++) {
            free(list->items[i].elements);
        }
        free(list->items);
        list->items = NULL;
    }
    list->count = 0;
}

int main(void) {
    TupleList list;
    size_t lengths[] = {2, 3, 2, 4};
    size_t num_tuples = sizeof(lengths) / sizeof(lengths[0]);

    list.count = num_tuples;
    list.items = malloc(list.count * sizeof(Tuple));
    if (list.items == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < list.count; i++) {
        list.items[i].length = lengths[i];
        list.items[i].elements = malloc(lengths[i] * sizeof(int));
        if (list.items[i].elements == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(list.items[j].elements);
            }
            free(list.items);
            return EXIT_FAILURE;
        }
        for (size_t j = 0; j < lengths[i]; j++) {
            list.items[i].elements[j] = (int)(i * 10 + j);
        }
    }

    size_t k = 2;
    if (remove_tuples_of_length_k(&list, k) != 0) {
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < list.count; i++) {
        printf("Tuple %zu (len %zu): ", i, list.items[i].length);
        for (size_t j = 0; j < list.items[i].length; j++) {
            printf("%d ", list.items[i].elements[j]);
        }
        printf("\n");
    }

    free_tuple_list(&list);
    return EXIT_SUCCESS;
}