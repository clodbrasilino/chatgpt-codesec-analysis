#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int add_checked(int64_t a, int64_t b, int64_t *result)
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
    size_t total;
    size_t row;
    size_t row_start;

    if (triangle == NULL || result == NULL || rows == 0) {
        return 0;
    }

    if (rows > SIZE_MAX / (rows + 1)) {
        return 0;
    }

    total = rows * (rows + 1) / 2;

    if (total > SIZE_MAX / sizeof(*sums)) {
        return 0;
    }

    sums = malloc(total * sizeof(*sums));
    if (sums == NULL) {
        return 0;
    }

    for (size_t i = 0; i < total; ++i) {
        sums[i] = triangle[i];
    }

    row_start = total - rows;

    for (row = rows - 1; row > 0; --row) {
        size_t parent_start = row_start - row;

        for (size_t column = 0; column < row; ++column) {
            int64_t child = sums[row_start + column] >
                            sums[row_start + column + 1]
                                ? sums[row_start + column]
                                : sums[row_start + column + 1];

            if (!add_checked(sums[parent_start + column], child,
                             &sums[parent_start + column])) {
                free(sums);
                return 0;
            }
        }

        row_start = parent_start;
    }

    *result = sums[0];
    free(sums);
    return 1;
}

int main(void)
{
    size_t rows;
    size_t total;
    int64_t *triangle = NULL;
    int64_t result;

    if (scanf("%zu", &rows) != 1 || rows == 0) {
        fputs("Invalid row count\n", stderr);
        return EXIT_FAILURE;
    }

    if (rows == SIZE_MAX || rows > SIZE_MAX / (rows + 1)) {
        fputs("Triangle size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    total = rows * (rows + 1) / 2;

    if (total > SIZE_MAX / sizeof(*triangle)) {
        fputs("Triangle size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    triangle = malloc(total * sizeof(*triangle));
    if (triangle == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < total; ++i) {
        errno = 0;
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64, &triangle[i]) != 1 || errno == ERANGE) {
            fputs("Invalid triangle element\n", stderr);
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    if (!maximum_path_sum(triangle, rows, &result)) {
        fputs("Unable to calculate maximum path sum\n", stderr);
        free(triangle);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        free(triangle);
        return EXIT_FAILURE;
    }

    free(triangle);
    return EXIT_SUCCESS;
}