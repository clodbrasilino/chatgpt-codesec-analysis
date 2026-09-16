#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stddef.h>
#include <limits.h>

static bool calculate_element_count(size_t rows, size_t *count)
{
    size_t first;
    size_t second;

    if (count == NULL || rows == 0 || rows == SIZE_MAX) {
        return false;
    }

    first = rows;
    second = rows + 1;

    if ((first & 1U) == 0U) {
        first /= 2;
    } else {
        second /= 2;
    }

    if (second != 0 && first > SIZE_MAX / second) {
        return false;
    }

    *count = first * second;
    return true;
}

static bool checked_add_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if ((right > 0 && left > INT64_MAX - right) ||
        (right < 0 && left < INT64_MIN - right)) {
        return false;
    }

    *result = left + right;
    return true;
}

static bool find_max_sum(const int64_t *triangle, size_t rows, int64_t *result)
{
    int64_t *sums;
    size_t element_count;
    size_t last_row_offset;

    if (triangle == NULL || result == NULL ||
        !calculate_element_count(rows, &element_count) ||
        rows > SIZE_MAX / sizeof(*sums)) {
        return false;
    }

    sums = malloc(rows * sizeof(*sums));
    if (sums == NULL) {
        return false;
    }

    last_row_offset = element_count - rows;

    for (size_t column = 0; column < rows; ++column) {
        sums[column] = triangle[last_row_offset + column];
    }

    for (size_t row = rows - 1; row-- > 0;) {
        size_t row_offset = row * (row + 1) / 2;

        for (size_t column = 0; column <= row; ++column) {
            int64_t child = sums[column] > sums[column + 1]
                                ? sums[column]
                                : sums[column + 1];

            if (!checked_add_int64(triangle[row_offset + column],
                                   child,
                                   &sums[column])) {
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
    size_t rows;
    size_t element_count;
    int64_t *triangle;
    int64_t maximum_sum;

    if (scanf("%zu", &rows) != 1 ||
        !calculate_element_count(rows, &element_count) ||
        element_count > SIZE_MAX / sizeof(*triangle)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    triangle = malloc(element_count * sizeof(*triangle));
    if (triangle == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < element_count; ++index) {
        if (scanf("%" SCNd64, &triangle[index]) != 1) {
            fputs("Invalid input\n", stderr);
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    if (!find_max_sum(triangle, rows, &maximum_sum)) {
        fputs("Unable to calculate maximum sum\n", stderr);
        free(triangle);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", maximum_sum);
    free(triangle);
    return EXIT_SUCCESS;
}