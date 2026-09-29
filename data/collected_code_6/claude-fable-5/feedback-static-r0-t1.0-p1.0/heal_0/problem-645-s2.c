#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define ROWS 4
#define COLS 3

int product_at_kth_index(const int tuples[][COLS], size_t rows, size_t cols, size_t k, long long *result)
{
    size_t i;
    long long product = 1;

    if (tuples == NULL || result == NULL) {
        return -1;
    }

    if (rows == 0U || k >= cols) {
        return -1;
    }

    for (i = 0U; i < rows; i++) {
        long long value = (long long)tuples[i][k];

        if (value != 0LL) {
            if (product > 0LL) {
                if (value > 0LL && product > (LLONG_MAX / value)) {
                    return -1;
                }
                if (value < 0LL && value < (LLONG_MIN / product)) {
                    return -1;
                }
            } else if (product < 0LL) {
                if (value > 0LL && product < (LLONG_MIN / value)) {
                    return -1;
                }
                if (value < 0LL && product < (LLONG_MAX / value)) {
                    return -1;
                }
            }
        }

        product *= value;
    }

    *result = product;
    return 0;
}

int main(void)
{
    const int tuples[ROWS][COLS] = {
        {5, 6, 7},
        {1, 3, 5},
        {8, 9, 19},
        {2, 4, 6}
    };
    size_t k = 2U;
    long long result = 0LL;
    int status;

    status = product_at_kth_index(tuples, (size_t)ROWS, (size_t)COLS, k, &result);

    if (status != 0) {
        (void)fprintf(stderr, "Error: invalid input or arithmetic overflow\n");
        return EXIT_FAILURE;
    }

    if (printf("Product at index %zu: %lld\n", k, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}