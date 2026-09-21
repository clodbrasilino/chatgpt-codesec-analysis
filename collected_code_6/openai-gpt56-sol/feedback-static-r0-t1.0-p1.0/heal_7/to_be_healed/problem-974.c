#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

#define INPUT_BUFFER_SIZE 256U

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch == EOF && ferror(stdin) ? -1 : 0;
}

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[INPUT_BUFFER_SIZE];
    char *end;
    intmax_t parsed;
    size_t length;

    if (value == NULL) {
        return -1;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    length = 0;
    while (length < sizeof buffer &&
           buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length == sizeof buffer) {
        if (discard_line() != 0) {
            return -1;
        }
        return -1;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (!feof(stdin)) {
        if (discard_line() != 0) {
            return -1;
        }
        return -1;
    } else if (ferror(stdin)) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE ||
        end == buffer ||
        parsed < INT64_MIN ||
        parsed > INT64_MAX) {
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

static int checked_triangle_size(size_t rows, size_t *element_count)
{
    size_t a;
    size_t b;
    size_t count;

    if (element_count == NULL || rows == 0 || rows == SIZE_MAX) {
        return -1;
    }

    a = rows;
    b = rows + 1;

    if ((a % 2U) == 0U) {
        a /= 2U;
    } else {
        b /= 2U;
    }

    if (a != 0 && b > SIZE_MAX / a) {
        return -1;
    }

    count = a * b;

    if (count > SIZE_MAX / sizeof(int64_t)) {
        return -1;
    }

    *element_count = count;
    return 0;
}

static int add_int64_checked(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return -1;
    }

    if ((right > 0 && left > INT64_MAX - right) ||
        (right < 0 && left < INT64_MIN - right)) {
        return -1;
    }

    *result = left + right;
    return 0;
}

static int minimum_total(const int64_t *triangle, size_t rows, int64_t *result)
{
    int64_t *dp;
    size_t element_count;
    size_t last_offset;

    if (triangle == NULL ||
        result == NULL ||
        checked_triangle_size(rows, &element_count) != 0 ||
        rows > SIZE_MAX / sizeof *dp) {
        return -1;
    }

    dp = malloc(rows * sizeof *dp);
    if (dp == NULL) {
        return -1;
    }

    last_offset = element_count - rows;

    for (size_t column = 0; column < rows; ++column) {
        dp[column] = triangle[last_offset + column];
    }

    for (size_t row = rows - 1; row > 0; --row) {
        size_t offset = ((row - 1) * row) / 2;

        for (size_t column = 0; column < row; ++column) {
            int64_t minimum = dp[column] < dp[column + 1]
                                  ? dp[column]
                                  : dp[column + 1];

            if (add_int64_checked(triangle[offset + column],
                                  minimum,
                                  &dp[column]) != 0) {
                free(dp);
                return -1;
            }
        }
    }

    *result = dp[0];
    free(dp);
    return 0;
}

int main(void)
{
    int64_t input_rows;
    size_t rows;
    size_t element_count;
    int64_t *triangle;
    int64_t result;

    if (read_int64(&input_rows) != 0 ||
        input_rows <= 0 ||
        (uintmax_t)input_rows > (uintmax_t)SIZE_MAX) {
        fputs("Invalid number of rows\n", stderr);
        return EXIT_FAILURE;
    }

    rows = (size_t)input_rows;

    if (checked_triangle_size(rows, &element_count) != 0) {
        fputs("Triangle is too large\n", stderr);
        return EXIT_FAILURE;
    }

    triangle = malloc(element_count * sizeof *triangle);
    if (triangle == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < element_count; ++index) {
        if (read_int64(&triangle[index]) != 0) {
            fputs("Invalid triangle value\n", stderr);
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    if (minimum_total(triangle, rows, &result) != 0) {
        fputs("Unable to calculate minimum path sum\n", stderr);
        free(triangle);
        return EXIT_FAILURE;
    }

    free(triangle);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}