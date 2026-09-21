#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

static int discard_line(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (strchr(buffer, '\n') != NULL) {
            return 0;
        }
    }

    return feof(stdin) ? 0 : -1;
}

static int read_int64(int64_t *value)
{
    char *line = NULL;
    size_t length = 0;
    size_t capacity = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];
    int complete = 0;

    if (value == NULL) {
        return -1;
    }

    while (!complete) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            if (ferror(stdin) || length == 0) {
                free(line);
                return -1;
            }
            complete = 1;
        } else {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t chunk_length = strlen(buffer);

            if (chunk_length > 0 && buffer[chunk_length - 1] == '\n') {
                --chunk_length;
                complete = 1;
            }

            if (chunk_length > SIZE_MAX - length - 1) {
                free(line);
                if (!complete) {
                    discard_line();
                }
                return -1;
            }

            size_t required = length + chunk_length + 1;

            if (required > capacity) {
                size_t new_capacity = capacity == 0 ? 64 : capacity;

                while (new_capacity < required) {
                    if (new_capacity > SIZE_MAX / 2) {
                        new_capacity = required;
                        break;
                    }
                    new_capacity *= 2;
                }

                char *new_line = realloc(line, new_capacity);
                if (new_line == NULL) {
                    free(line);
                    if (!complete) {
                        discard_line();
                    }
                    return -1;
                }

                line = new_line;
                capacity = new_capacity;
            }

            if (chunk_length != 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(line + length, buffer, chunk_length);
                length += chunk_length;
            }
        }
    }

    if (line == NULL) {
        line = malloc(1);
        if (line == NULL) {
            return -1;
        }
    }

    line[length] = '\0';

    char *start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    char *end = NULL;
    intmax_t parsed = strtoimax(start, &end, 10);

    if (errno == ERANGE || end == start ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(line);
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return -1;
    }

    *value = (int64_t)parsed;
    free(line);
    return 0;
}

static int minimum_total(const int64_t *triangle, size_t rows, int64_t *result)
{
    if (triangle == NULL || result == NULL || rows == 0 ||
        rows == SIZE_MAX || rows > SIZE_MAX / (rows + 1) ||
        rows > SIZE_MAX / sizeof(int64_t)) {
        return -1;
    }

    size_t element_count = rows * (rows + 1) / 2;
    if (element_count > SIZE_MAX / sizeof(*triangle)) {
        return -1;
    }

    int64_t *dp = malloc(rows * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    size_t last_offset = rows * (rows - 1) / 2;

    for (size_t column = 0; column < rows; ++column) {
        dp[column] = triangle[last_offset + column];
    }

    for (size_t row = rows - 1; row > 0; --row) {
        size_t offset = (row - 1) * row / 2;

        for (size_t column = 0; column < row; ++column) {
            int64_t minimum =
                dp[column] < dp[column + 1] ? dp[column] : dp[column + 1];
            int64_t value = triangle[offset + column];

            if ((minimum > 0 && value > INT64_MAX - minimum) ||
                (minimum < 0 && value < INT64_MIN - minimum)) {
                free(dp);
                return -1;
            }

            dp[column] = value + minimum;
        }
    }

    *result = dp[0];
    free(dp);
    return 0;
}

int main(void)
{
    int64_t input_rows;

    if (read_int64(&input_rows) != 0 || input_rows <= 0 ||
        (uintmax_t)input_rows > (uintmax_t)SIZE_MAX) {
        fputs("Invalid number of rows\n", stderr);
        return EXIT_FAILURE;
    }

    size_t rows = (size_t)input_rows;

    if (rows == SIZE_MAX || rows > SIZE_MAX / (rows + 1)) {
        fputs("Triangle is too large\n", stderr);
        return EXIT_FAILURE;
    }

    size_t element_count = rows * (rows + 1) / 2;

    if (element_count > SIZE_MAX / sizeof(int64_t) ||
        rows > SIZE_MAX / sizeof(int64_t)) {
        fputs("Triangle is too large\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *triangle = malloc(element_count * sizeof(*triangle));
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

    int64_t result;

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