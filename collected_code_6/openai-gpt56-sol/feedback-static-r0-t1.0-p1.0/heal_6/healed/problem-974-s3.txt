#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

static int read_line(char **line)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 128;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
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
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return -1;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
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
    char *buffer = NULL;
    char *start;
    char *end;
    intmax_t parsed;

    if (value == NULL || read_line(&buffer) != 0) {
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
    char *buffer = NULL;
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_line(&buffer) != 0) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(buffer);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        parsed > (uintmax_t)SIZE_MAX) {
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

static int minimum_total(const int64_t *const *triangle, size_t rows,
                         int64_t *result)
{
    int64_t *dp;

    if (triangle == NULL || result == NULL || rows == 0 ||
        rows > SIZE_MAX / sizeof *dp) {
        return -1;
    }

    for (size_t i = 0; i < rows; ++i) {
        if (triangle[i] == NULL) {
            return -1;
        }
    }

    dp = malloc(rows * sizeof *dp);
    if (dp == NULL) {
        return -1;
    }

    for (size_t i = 0; i < rows; ++i) {
        dp[i] = triangle[rows - 1][i];
    }

    for (size_t i = rows - 1; i > 0; --i) {
        for (size_t j = 0; j < i; ++j) {
            int64_t value = triangle[i - 1][j];
            int64_t minimum = dp[j] < dp[j + 1] ? dp[j] : dp[j + 1];

            if ((value > 0 && minimum > INT64_MAX - value) ||
                (value < 0 && minimum < INT64_MIN - value)) {
                free(dp);
                return -1;
            }

            dp[j] = value + minimum;
        }
    }

    *result = dp[0];
    free(dp);
    return 0;
}

int main(void)
{
    size_t rows;
    int64_t **triangle;
    int64_t result;
    int status = EXIT_FAILURE;

    if (read_size(&rows) != 0 || rows == 0 ||
        rows > SIZE_MAX / sizeof *triangle) {
        fprintf(stderr, "Invalid row count\n");
        return EXIT_FAILURE;
    }

    triangle = calloc(rows, sizeof *triangle);
    if (triangle == NULL) {
        perror("calloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < rows; ++i) {
        size_t elements = i + 1;

        if (elements > SIZE_MAX / sizeof **triangle) {
            fprintf(stderr, "Triangle is too large\n");
            goto cleanup;
        }

        triangle[i] = malloc(elements * sizeof **triangle);
        if (triangle[i] == NULL) {
            perror("malloc");
            goto cleanup;
        }

        for (size_t j = 0; j < elements; ++j) {
            if (read_int64(&triangle[i][j]) != 0) {
                fprintf(stderr, "Invalid triangle value\n");
                goto cleanup;
            }
        }
    }

    if (minimum_total((const int64_t *const *)triangle, rows, &result) != 0) {
        fprintf(stderr, "Unable to compute minimum path sum\n");
        goto cleanup;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        perror("printf");
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    for (size_t i = 0; i < rows; ++i) {
        free(triangle[i]);
    }

    free(triangle);
    return status;
}