#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

static int read_line(char *buffer, size_t size)
{
    if (buffer == NULL || size < 2 || fgets(buffer, size, stdin) == NULL) {
        return -1;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        return -1;
    }

    return 0;
}

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *start;
    char *end;
    intmax_t parsed;

    if (value == NULL || read_line(buffer, sizeof(buffer)) != 0) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_line(buffer, sizeof(buffer)) != 0) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        parsed > (uintmax_t)SIZE_MAX) {
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

static int checked_triangle_elements(size_t rows, size_t *elements)
{
    size_t a;
    size_t b;

    if (elements == NULL || rows == 0 || rows == SIZE_MAX) {
        return -1;
    }

    a = rows;
    b = rows + 1;

    if ((a & 1U) == 0U) {
        a /= 2;
    } else {
        b /= 2;
    }

    if (a != 0 && b > SIZE_MAX / a) {
        return -1;
    }

    *elements = a * b;
    return 0;
}

static int checked_add_int64(int64_t left, int64_t right, int64_t *result)
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

static int maximum_path_sum(const int64_t *triangle, size_t rows,
                            int64_t *result)
{
    int64_t *sums;
    size_t elements;
    size_t offset;

    if (triangle == NULL || result == NULL ||
        checked_triangle_elements(rows, &elements) != 0 ||
        rows > SIZE_MAX / sizeof(*sums)) {
        return -1;
    }

    sums = malloc(rows * sizeof(*sums));
    if (sums == NULL) {
        return -1;
    }

    offset = elements - rows;

    for (size_t column = 0; column < rows; ++column) {
        sums[column] = triangle[offset + column];
    }

    for (size_t row = rows - 1; row > 0; --row) {
        offset = row * (row - 1) / 2;

        for (size_t column = 0; column < row; ++column) {
            int64_t best = sums[column] > sums[column + 1]
                               ? sums[column]
                               : sums[column + 1];

            if (checked_add_int64(triangle[offset + column], best,
                                  &sums[column]) != 0) {
                free(sums);
                return -1;
            }
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

    if (read_size(&rows) != 0 ||
        checked_triangle_elements(rows, &elements) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

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
        if (read_int64(&triangle[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    if (maximum_path_sum(triangle, rows, &result) != 0) {
        fputs("Unable to calculate path sum\n", stderr);
        free(triangle);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);
    free(triangle);

    return EXIT_SUCCESS;
}