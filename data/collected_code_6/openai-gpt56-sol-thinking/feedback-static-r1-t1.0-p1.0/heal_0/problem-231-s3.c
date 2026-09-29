#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static bool triangle_element_count(size_t rows, size_t *count)
{
    size_t a;
    size_t b;

    if (count == NULL || rows == SIZE_MAX) {
        return false;
    }

    if (rows % 2U == 0U) {
        a = rows / 2U;
        b = rows + 1U;
    } else {
        a = rows;
        b = (rows + 1U) / 2U;
    }

    if (a != 0U && b > SIZE_MAX / a) {
        return false;
    }

    *count = a * b;
    return true;
}

static bool checked_add_int64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return false;
    }

    *result = a + b;
    return true;
}

static bool maximum_triangle_sum(const int64_t *triangle, size_t rows,
                                 size_t element_count, int64_t *result)
{
    int64_t *sums;
    size_t expected_count;
    size_t last_row_start;
    size_t row;

    if (result == NULL ||
        !triangle_element_count(rows, &expected_count) ||
        expected_count != element_count) {
        return false;
    }

    if (rows == 0U) {
        *result = 0;
        return true;
    }

    if (triangle == NULL || rows > SIZE_MAX / sizeof(*sums)) {
        return false;
    }

    sums = malloc(rows * sizeof(*sums));
    if (sums == NULL) {
        return false;
    }

    last_row_start = element_count - rows;
    for (size_t column = 0U; column < rows; ++column) {
        sums[column] = triangle[last_row_start + column];
    }

    row = rows - 1U;
    while (row > 0U) {
        size_t row_start;

        --row;
        row_start = row * (row + 1U) / 2U;

        for (size_t column = 0U; column <= row; ++column) {
            int64_t best_child = sums[column] > sums[column + 1U]
                                     ? sums[column]
                                     : sums[column + 1U];

            if (!checked_add_int64(triangle[row_start + column],
                                   best_child, &sums[column])) {
                free(sums);
                return false;
            }
        }
    }

    *result = sums[0];
    free(sums);
    return true;
}

int main(void)
{
    uintmax_t input_rows;
    size_t rows;
    size_t element_count;
    int64_t *triangle = NULL;
    int64_t maximum;

    if (fscanf(stdin, "%" SCNuMAX, &input_rows) != 1) {
        fputs("Invalid row count\n", stderr);
        return EXIT_FAILURE;
    }

    if (input_rows > SIZE_MAX) {
        fputs("Row count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    rows = (size_t)input_rows;

    if (!triangle_element_count(rows, &element_count) ||
        element_count > SIZE_MAX / sizeof(*triangle)) {
        fputs("Triangle is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (element_count > 0U) {
        triangle = malloc(element_count * sizeof(*triangle));
        if (triangle == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < element_count; ++i) {
        if (fscanf(stdin, "%" SCNd64, &triangle[i]) != 1) {
            fputs("Invalid triangle data\n", stderr);
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    if (!maximum_triangle_sum(triangle, rows, element_count, &maximum)) {
        fputs("Unable to calculate maximum sum\n", stderr);
        free(triangle);
        return EXIT_FAILURE;
    }

    free(triangle);

    if (fprintf(stdout, "%" PRId64 "\n", maximum) < 0 ||
        fflush(stdout) == EOF) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}