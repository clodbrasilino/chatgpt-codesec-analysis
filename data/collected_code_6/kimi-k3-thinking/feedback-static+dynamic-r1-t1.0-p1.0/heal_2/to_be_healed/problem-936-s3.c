#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int key;
    int value;
} Tuple;

int rearrange_tuples(Tuple *tuples, size_t tuple_count, const int *order, size_t order_size)
{
    Tuple *result;
    unsigned char *used;
    size_t i;
    size_t o;
    size_t out_index;
    size_t result_size;
    int status;

    if (tuples == NULL) {
        return -1;
    }
    if (order == NULL && order_size > 0) {
        return -1;
    }
    if (tuple_count == 0) {
        return 0;
    }

    if (tuple_count > SIZE_MAX / sizeof(Tuple)) {
        return -1;
    }
    result_size = tuple_count * sizeof(Tuple);

    result = (Tuple *)malloc(result_size);
    if (result == NULL) {
        return -1;
    }

    used = (unsigned char *)calloc(tuple_count, sizeof(unsigned char));
    if (used == NULL) {
        free(result);
        result = NULL;
        return -1;
    }

    out_index = 0;
    for (o = 0; o < order_size; o++) {
        for (i = 0; i < tuple_count; i++) {
            if (!used[i] && tuples[i].key == order[o]) {
                result[out_index] = tuples[i];
                out_index++;
                used[i] = 1;
            }
        }
    }

    for (i = 0; i < tuple_count; i++) {
        if (!used[i]) {
            result[out_index] = tuples[i];
            out_index++;
        }
    }

    status = -1;
    if (out_index == tuple_count) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(tuples, result, result_size);
        status = 0;
    }

    free(used);
    used = NULL;
    free(result);
    result = NULL;

    return status;
}

static void print_tuples(const Tuple *tuples, size_t tuple_count)
{
    size_t i;

    for (i = 0; i < tuple_count; i++) {
        printf("(%d, %d) ", tuples[i].key, tuples[i].value);
    }
    printf("\n");
}

int main(void)
{
    Tuple tuples[] = {
        {2, 20},
        {1, 10},
        {4, 40},
        {3, 30},
        {1, 15}
    };
    int order[] = {1, 2, 3};
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    size_t order_size = sizeof(order) / sizeof(order[0]);

    printf("Before: ");
    print_tuples(tuples, tuple_count);

    if (rearrange_tuples(tuples, tuple_count, order, order_size) != 0) {
        fprintf(stderr, "Error: failed to rearrange tuples\n");
        return EXIT_FAILURE;
    }

    printf("After:  ");
    print_tuples(tuples, tuple_count);

    return EXIT_SUCCESS;
}