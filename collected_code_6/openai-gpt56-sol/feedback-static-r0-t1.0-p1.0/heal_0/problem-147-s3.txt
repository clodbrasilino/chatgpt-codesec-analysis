#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int add_int64(int64_t a, int64_t b, int64_t *result)
{
    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int maximum_path_sum(const int64_t *triangle, size_t rows, int64_t *result)
{
    int64_t *sums = NULL;
    size_t last_row_start;
    size_t row;

    if (triangle == NULL || result == NULL || rows == 0) {
        return 0;
    }

    if (rows > SIZE_MAX / (rows + 1)) {
        return 0;
    }

    if (rows > SIZE_MAX / sizeof(*sums)) {
        return 0;
    }

    sums = malloc(rows * sizeof(*sums));
    if (sums == NULL) {
        return 0;
    }

    last_row_start = rows * (rows - 1) / 2;

    for (size_t column = 0; column < rows; ++column) {
        sums[column] = triangle[last_row_start + column];
    }

    for (row = rows - 1; row > 0; --row) {
        size_t row_start = row * (row - 1) / 2;

        for (size_t column = 0; column < row; ++column) {
            int64_t best_child =
                sums[column] > sums[column + 1] ? sums[column] : sums[column + 1];

            if (!add_int64(triangle[row_start + column], best_child,
                           &sums[column])) {
                free(sums);
                return 0;
            }
        }
    }

    *result = sums[0];
    free(sums);
    return 1;
}

int main(void)
{
    size_t rows;
    size_t element_count;
    int64_t *triangle = NULL;
    int64_t result;

    if (scanf("%zu", &rows) != 1 || rows == 0) {
        return EXIT_FAILURE;
    }

    if (rows == SIZE_MAX || rows > SIZE_MAX / (rows + 1)) {
        return EXIT_FAILURE;
    }

    element_count = rows * (rows + 1) / 2;

    if (element_count > SIZE_MAX / sizeof(*triangle)) {
        return EXIT_FAILURE;
    }

    triangle = malloc(element_count * sizeof(*triangle));
    if (triangle == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < element_count; ++index) {
        if (scanf("%" SCNd64, &triangle[index]) != 1) {
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    if (!maximum_path_sum(triangle, rows, &result)) {
        free(triangle);
        return EXIT_FAILURE;
    }

    free(triangle);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}