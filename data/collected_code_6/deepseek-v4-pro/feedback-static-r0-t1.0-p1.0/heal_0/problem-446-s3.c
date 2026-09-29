#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
} List;

typedef struct {
    int *elements;
    int size;
} Tuple;

int *count_occurrences(List *list, Tuple *tuple, int *result_size) {
    if (list == NULL || tuple == NULL || result_size == NULL) {
        return NULL;
    }

    int *counts = (int *)malloc(list->size * sizeof(int));
    if (counts == NULL) {
        return NULL;
    }

    for (int i = 0; i < list->size; i++) {
        counts[i] = 0;
        for (int j = 0; j < tuple->size; j++) {
            if (list->elements[i] == tuple->elements[j]) {
                counts[i]++;
            }
        }
    }

    *result_size = list->size;
    return counts;
}

int main(void) {
    int list_data[] = {1, 2, 3, 4, 5};
    int tuple_data[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};

    List list;
    list.elements = list_data;
    list.size = sizeof(list_data) / sizeof(list_data[0]);

    Tuple tuple;
    tuple.elements = tuple_data;
    tuple.size = sizeof(tuple_data) / sizeof(tuple_data[0]);

    int result_size = 0;
    int *counts = count_occurrences(&list, &tuple, &result_size);

    if (counts != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%d: %d\n", list.elements[i], counts[i]);
        }
        free(counts);
    } else {
        fprintf(stderr, "Error: Failed to allocate memory or invalid input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}