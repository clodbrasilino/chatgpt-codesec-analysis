#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} IntCollection;

int *count_occurrences(IntCollection tuple, IntCollection list) {
    if (list.size == 0) {
        return NULL;
    }

    int *counts = (int *)calloc(list.size, sizeof(int));
    if (counts == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < list.size; i++) {
        for (size_t j = 0; j < tuple.size; j++) {
            if (tuple.elements[j] == list.elements[i]) {
                counts[i]++;
            }
        }
    }

    return counts;
}

int main(void) {
    int tuple_arr[] = {1, 2, 3, 2, 4, 1, 2};
    int list_arr[] = {1, 2, 5};

    IntCollection tuple = {tuple_arr, sizeof(tuple_arr) / sizeof(tuple_arr[0])};
    IntCollection list = {list_arr, sizeof(list_arr) / sizeof(list_arr[0])};

    int *counts = count_occurrences(tuple, list);

    if (counts == NULL) {
        if (list.size > 0) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        return 0;
    }

    for (size_t i = 0; i < list.size; i++) {
        printf("%d: %d\n", list.elements[i], counts[i]);
    }

    free(counts);

    return 0;
}