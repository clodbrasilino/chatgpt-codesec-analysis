#include <stdio.h>
#include <stdlib.h>

int* get_last_elements(int **sublists, const size_t *sizes, size_t num_sublists) {
    if (!sublists || !sizes || num_sublists == 0) {
        return NULL;
    }

    int *last_elements = (int *)malloc(num_sublists * sizeof(int));
    if (!last_elements) {
        return NULL;
    }

    for (size_t i = 0; i < num_sublists; i++) {
        if (!sublists[i] || sizes[i] == 0) {
            free(last_elements);
            return NULL;
        }
        last_elements[i] = sublists[i][sizes[i] - 1];
    }

    return last_elements;
}

int main(void) {
    size_t num_sublists = 3;
    const size_t sizes[] = {3, 2, 4};

    int **sublists = (int **)malloc(num_sublists * sizeof(int *));
    if (!sublists) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < num_sublists; i++) {
        sublists[i] = (int *)malloc(sizes[i] * sizeof(int));
        if (!sublists[i]) {
            for (size_t j = 0; j < i; j++) {
                free(sublists[j]);
            }
            free(sublists);
            return EXIT_FAILURE;
        }
    }

    sublists[0][0] = 1;
    sublists[0][1] = 2;
    sublists[0][2] = 3;

    sublists[1][0] = 4;
    sublists[1][1] = 5;

    sublists[2][0] = 6;
    sublists[2][1] = 7;
    sublists[2][2] = 8;
    sublists[2][3] = 9;

    int *last_elements = get_last_elements(sublists, sizes, num_sublists);
    if (!last_elements) {
        for (size_t i = 0; i < num_sublists; i++) {
            free(sublists[i]);
        }
        free(sublists);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < num_sublists; i++) {
        printf("%d\n", last_elements[i]);
    }

    free(last_elements);
    for (size_t i = 0; i < num_sublists; i++) {
        free(sublists[i]);
    }
    free(sublists);

    return EXIT_SUCCESS;
}