#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[128];

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (value == NULL || scanf("%127s", token) != 1) {
        return -1;
    }

    char *end;
    errno = 0;
    intmax_t parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

static int read_size(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[128];

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (value == NULL || scanf("%127s", token) != 1 || token[0] == '-') {
        return -1;
    }

    char *end;
    errno = 0;
    uintmax_t parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' || parsed > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int input_has_only_whitespace(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF) {
        if (!isspace((unsigned char)ch)) {
            return 0;
        }
    }

    return !ferror(stdin);
}

static int find_maximum_sum(int64_t *const *triangle, size_t rows,
                            int64_t *result)
{
    if (triangle == NULL || result == NULL || rows == 0 ||
        triangle[rows - 1] == NULL ||
        rows > SIZE_MAX / sizeof(int64_t)) {
        return -1;
    }

    int64_t *sums = malloc(rows * sizeof(*sums));
    if (sums == NULL) {
        return -1;
    }

    for (size_t col = 0; col < rows; ++col) {
        sums[col] = triangle[rows - 1][col];
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
            int64_t value = triangle[row - 1][col];

            if ((best > 0 && value > INT64_MAX - best) ||
                (best < 0 && value < INT64_MIN - best)) {
                free(sums);
                return -1;
            }

            sums[col] = value + best;
        }
    }

    *result = sums[0];
    free(sums);
    return 0;
}

int main(void)
{
    size_t rows;

    if (read_size(&rows) != 0 || rows == 0 ||
        rows > SIZE_MAX / sizeof(int64_t *)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t **triangle = calloc(rows, sizeof(*triangle));
    if (triangle == NULL) {
        perror("calloc");
        return EXIT_FAILURE;
    }

    int status = EXIT_FAILURE;

    for (size_t row = 0; row < rows; ++row) {
        size_t count = row + 1;

        if (count > SIZE_MAX / sizeof(*triangle[row])) {
            fputs("Input is too large\n", stderr);
            goto cleanup;
        }

        triangle[row] = malloc(count * sizeof(*triangle[row]));
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

    if (!input_has_only_whitespace()) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
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