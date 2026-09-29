#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

static int read_line(char **line)
{
    if (line == NULL) {
        return -1;
    }

    size_t capacity = 64;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            if (ch == EOF && length == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length + 1) {
                free(buffer);
                return -1;
            }

            char *resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

static int read_int64(int64_t *value)
{
    if (value == NULL) {
        return -1;
    }

    char *buffer = NULL;

    if (read_line(&buffer) != 0) {
        return -1;
    }

    char *p = buffer;
    while (isspace((unsigned char)*p)) {
        ++p;
    }

    errno = 0;
    char *end = NULL;
    intmax_t parsed = strtoimax(p, &end, 10);

    if (p == end || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return -1;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 0;
}

static int read_size(size_t *value)
{
    if (value == NULL) {
        return -1;
    }

    char *buffer = NULL;

    if (read_line(&buffer) != 0) {
        return -1;
    }

    char *p = buffer;
    while (isspace((unsigned char)*p)) {
        ++p;
    }

    if (*p == '-') {
        free(buffer);
        return -1;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(p, &end, 10);

    if (p == end || errno == ERANGE ||
        parsed == 0 || parsed > SIZE_MAX) {
        free(buffer);
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return -1;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 0;
}

static int find_maximum_sum(int64_t *const *triangle,
                            size_t rows,
                            int64_t *result)
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