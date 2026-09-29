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

    *line = NULL;

    size_t capacity = 128;
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

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length >= capacity - 1) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
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

    char *start = buffer;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    char *end = NULL;
    intmax_t parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
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

    char *start = buffer;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(buffer);
        return -1;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE ||
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

static int find_maximum_sum(int64_t *const *triangle,
                            size_t rows,
                            int64_t *result)
{
    if (triangle == NULL || result == NULL || rows == 0 ||
        rows > SIZE_MAX / sizeof(int64_t) ||
        triangle[rows - 1] == NULL) {
        return -1;
    }

    int64_t *sums = malloc(rows * sizeof(*sums));

    if (sums == NULL) {
        return -1;
    }

    for (size_t column = 0; column < rows; ++column) {
        sums[column] = triangle[rows - 1][column];
    }

    for (size_t row = rows - 1; row > 0; --row) {
        if (triangle[row - 1] == NULL) {
            free(sums);
            return -1;
        }

        for (size_t column = 0; column < row; ++column) {
            int64_t best = sums[column] > sums[column + 1]
                               ? sums[column]
                               : sums[column + 1];

            if (checked_add_int64(triangle[row - 1][column],
                                  best,
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
    size_t rows = 0;

    if (read_size(&rows) != 0 ||
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
        if (row == SIZE_MAX) {
            fputs("Input is too large\n", stderr);
            goto cleanup;
        }

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

        for (size_t column = 0; column < count; ++column) {
            if (read_int64(&triangle[row][column]) != 0) {
                fputs("Invalid input\n", stderr);
                goto cleanup;
            }
        }
    }

    int64_t maximum_sum = 0;

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