#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int32_t find_tuple_inversions(int32_t **tuples, size_t num_tuples, size_t tuple_size) {
    if (tuples == NULL || num_tuples == 0 || tuple_size < 2) {
        return -1;
    }

    int32_t inversion_count = 0;

    for (size_t i = 0; i < num_tuples; i++) {
        if (tuples[i] == NULL) {
            return -1;
        }
        for (size_t j = 0; j + 1 < tuple_size; j++) {
            if (tuples[i][j] > tuples[i][j + 1]) {
                inversion_count++;
            }
        }
    }

    return inversion_count;
}

int main(void) {
    int32_t t0[] = {1, 2, 3};
    int32_t t1[] = {2, 1, 3};
    int32_t t2[] = {3, 2, 1};

    size_t num_tuples = 3;
    size_t tuple_size = 3;

    int32_t **tuples = (int32_t **)malloc(num_tuples * sizeof(int32_t *));
    if (tuples == NULL) {
        return EXIT_FAILURE;
    }

    tuples[0] = t0;
    tuples[1] = t1;
    tuples[2] = t2;

    int32_t inversions = find_tuple_inversions(tuples, num_tuples, tuple_size);

    printf("%d\n", inversions);

    free(tuples);

    return EXIT_SUCCESS;
}