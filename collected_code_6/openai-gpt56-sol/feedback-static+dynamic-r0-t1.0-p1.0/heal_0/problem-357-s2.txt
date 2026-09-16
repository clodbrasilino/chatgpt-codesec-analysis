#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t count;
} Tuple;

int find_maximum(const Tuple *tuples, size_t tuple_count, int *maximum)
{
    if (tuples == NULL || maximum == NULL || tuple_count == 0) {
        return 0;
    }

    size_t first_tuple = 0;

    while (first_tuple < tuple_count && tuples[first_tuple].count == 0) {
        ++first_tuple;
    }

    if (first_tuple == tuple_count || tuples[first_tuple].elements == NULL) {
        return 0;
    }

    int result = tuples[first_tuple].elements[0];

    for (size_t i = first_tuple; i < tuple_count; ++i) {
        if (tuples[i].count > 0 && tuples[i].elements == NULL) {
            return 0;
        }

        for (size_t j = 0; j < tuples[i].count; ++j) {
            if (tuples[i].elements[j] > result) {
                result = tuples[i].elements[j];
            }
        }
    }

    *maximum = result;
    return 1;
}

int main(void)
{
    Tuple tuples[] = {
        {(int[]){3, 7, 2}, 3},
        {(int[]){12, 5}, 2},
        {(int[]){-4, 9, 1, 6}, 4}
    };
    const size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    int maximum = 0;

    if (!find_maximum(tuples, tuple_count, &maximum)) {
        fputs("Unable to find a maximum element.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Maximum element: %d\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}