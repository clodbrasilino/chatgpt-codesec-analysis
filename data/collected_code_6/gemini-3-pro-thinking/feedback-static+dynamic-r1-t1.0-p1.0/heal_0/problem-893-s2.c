#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int get_last_elements(int **sublists, const size_t *sizes, size_t num_sublists, int *out) {
    if (sublists == NULL || sizes == NULL || out == NULL) {
        return -1;
    }

    for (size_t i = 0; i < num_sublists; ++i) {
        if (sublists[i] == NULL || sizes[i] == 0) {
            return -2;
        }
        out[i] = sublists[i][sizes[i] - 1];
    }

    return 0;
}

int main(void) {
    size_t num_sublists = 3;
    
    int **sublists = malloc(num_sublists * sizeof(int *));
    size_t *sizes = malloc(num_sublists * sizeof(size_t));
    int *out = malloc(num_sublists * sizeof(int));

    if (sublists == NULL || sizes == NULL || out == NULL) {
        free(sublists);
        free(sizes);
        free(out);
        return EXIT_FAILURE;
    }

    sizes[0] = 3;
    sizes[1] = 2;
    sizes[2] = 4;

    for (size_t i = 0; i < num_sublists; ++i) {
        sublists[i] = malloc(sizes[i] * sizeof(int));
        if (sublists[i] == NULL) {
            for (size_t j = 0; j < i; ++j) {
                free(sublists[j]);
            }
            free(sublists);
            free(sizes);
            free(out);
            return EXIT_FAILURE;
        }
    }

    sublists[0][0] = 10;
    sublists[0][1] = 20;
    sublists[0][2] = 30;

    sublists[1][0] = 40;
    sublists[1][1] = 50;

    sublists[2][0] = 60;
    sublists[2][1] = 70;
    sublists[2][2] = 80;
    sublists[2][3] = 90;

    if (get_last_elements(sublists, sizes, num_sublists, out) == 0) {
        for (size_t i = 0; i < num_sublists; ++i) {
            printf("%d\n", out[i]);
        }
    }

    for (size_t i = 0; i < num_sublists; ++i) {
        free(sublists[i]);
    }
    free(sublists);
    free(sizes);
    free(out);

    return EXIT_SUCCESS;
}