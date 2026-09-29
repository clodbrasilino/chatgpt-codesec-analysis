#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int read_int64(int64_t *value)
{
    char buffer[128];

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    char *p = buffer;
    while (isspace((unsigned char)*p)) {
        ++p;
    }

    errno = 0;
    char *end;
    intmax_t parsed = strtoimax(p, &end, 10);

    if (p == end || errno == ERANGE || parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

static int read_size(size_t *value)
{
    char buffer[128];

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    char *p = buffer;
    while (isspace((unsigned char)*p)) {
        ++p;
    }

    if (*p == '-') {
        return -1;
    }

    errno = 0;
    char *end;
    uintmax_t parsed = strtoumax(p, &end, 10);

    if (p == end || errno == ERANGE || parsed == 0 || parsed > SIZE_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int find_maximum_sum(int64_t **triangle, size_t rows, int64_t *result)
{
    if (triangle == NULL || result == NULL || rows == 0 ||
        triangle[rows - 1] == NULL ||
        rows > SIZE_MAX / sizeof(int64_t)) {
        return -1;
    }

    int64_t *sums = malloc(rows * sizeof *sums);
    if (sums == NULL) {
        return -1;
    }

    for (size_t i = 0; i < rows; ++i) {
        sums[i] = triangle[rows - 1][i];
    }

    for (size_t row = rows - 1; row > 0; --row) {
        if (triangle[row - 1] == NULL) {
            free(sums);
            return -1;
        }

        for (size_t col = 0; col < row; ++col) {
            int64_t best = sums[col] > sums[col + 1]
                               ? sums[col]
                               : sums[col + 1];
            int64_t current = triangle[row - 1][col];

            if ((best > 0 && current > INT64_MAX - best) ||
                (best < 0 && current < INT64_MIN - best)) {
                free(sums);
                return -1;
            }

            sums[col] = current + best;
        }
    }

    *result = sums[0];
    free(sums);
    return 0;
}

int main(void)
{
    size_t rows;

    if (read_size(&rows) != 0 ||
        rows > SIZE_MAX / sizeof(int64_t *)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t **triangle = calloc(rows, sizeof *triangle);
    if (triangle == NULL) {
        perror("calloc");
        return EXIT_FAILURE;
    }

    int status = EXIT_FAILURE;

    for (size_t row = 0; row < rows; ++row) {
        size_t count = row + 1;

        if (count > SIZE_MAX / sizeof *triangle[row]) {
            fputs("Input is too large\n", stderr);
            goto cleanup;
        }

        triangle[row] = malloc(count * sizeof *triangle[row]);
        if (triangle[row] == NULL) {
            perror("malloc");
            goto cleanup;
        }

        for (size_t col = 0; col < count; ++col) {
            if (read_int64(&triangle[row][col]) != 0) {
                fputs("Invalid input\n", stderr);
                goto cleanup;
            }
        }
    }

    int64_t maximum_sum;
    if (find_maximum_sum(triangle, rows, &maximum_sum) != 0) {
        fputs("Unable to calculate maximum sum\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRId64 "\n", maximum_sum) < 0) {
        perror("printf");
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    for (size_t row = 0; row < rows; ++row) {
        free(triangle[row]);
    }

    free(triangle);
    return status;
}