#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int maximum_path_sum(const int64_t *triangle, size_t rows, int64_t *result)
{
    int64_t *sums;
    size_t offset;

    if (triangle == NULL || result == NULL || rows == 0 ||
        rows > SIZE_MAX / rows ||
        rows * (rows + 1U) / 2U > SIZE_MAX / sizeof(*triangle)) {
        return -1;
    }

    if (rows > SIZE_MAX / sizeof(*sums)) {
        return -1;
    }

    sums = malloc(rows * sizeof(*sums));
    if (sums == NULL) {
        return -1;
    }

    offset = rows * (rows - 1U) / 2U;
    for (size_t column = 0; column < rows; ++column) {
        sums[column] = triangle[offset + column];
    }

    for (size_t row = rows - 1U; row > 0; --row) {
        offset = (row - 1U) * row / 2U;

        for (size_t column = 0; column < row; ++column) {
            int64_t best = sums[column] > sums[column + 1U]
                               ? sums[column]
                               : sums[column + 1U];
            int64_t value = triangle[offset + column];

            if ((best > 0 && value > INT64_MAX - best) ||
                (best < 0 && value < INT64_MIN - best)) {
                free(sums);
                return -1;
            }

            sums[column] = value + best;
        }
    }

    *result = sums[0];
    free(sums);
    return 0;
}

int main(void)
{
    size_t rows;
    size_t elements;
    int64_t *triangle;
    int64_t result;

    if (scanf("%zu", &rows) != 1 || rows == 0 ||
        rows == SIZE_MAX ||
        rows > SIZE_MAX / (rows + 1U)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    elements = rows * (rows + 1U) / 2U;
    if (elements > SIZE_MAX / sizeof(*triangle)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    triangle = malloc(elements * sizeof(*triangle));
    if (triangle == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < elements; ++i) {
        if (scanf("%" SCNd64, &triangle[i]) != 1) {
            fputs("Invalid input\n", stderr);
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    if (maximum_path_sum(triangle, rows, &result) != 0) {
        fputs("Unable to calculate path sum\n", stderr);
        free(triangle);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);
    free(triangle);
    return EXIT_SUCCESS;
}