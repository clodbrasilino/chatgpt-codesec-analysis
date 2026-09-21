#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>

static int read_token(char **token)
{
    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    size_t length = 0;
    size_t capacity = 32;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        free(buffer);
        return -1;
    }

    for (;;) {
        if (length > SIZE_MAX - 2) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == EOF || isspace((unsigned char)ch)) {
            break;
        }
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *token = buffer;
    return 0;
}

static int read_int64(int64_t *value)
{
    if (value == NULL) {
        return -1;
    }

    char *token = NULL;

    if (read_token(&token) != 0) {
        return -1;
    }

    char *end = NULL;
    errno = 0;
    intmax_t parsed = strtoimax(token, &end, 10);

    int valid = errno != ERANGE &&
                end != token &&
                *end == '\0' &&
                parsed >= INT64_MIN &&
                parsed <= INT64_MAX;

    free(token);

    if (!valid) {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

static int read_size(size_t *value)
{
    if (value == NULL) {
        return -1;
    }

    char *token = NULL;

    if (read_token(&token) != 0) {
        return -1;
    }

    if (token[0] == '-') {
        free(token);
        return -1;
    }

    char *end = NULL;
    errno = 0;
    uintmax_t parsed = strtoumax(token, &end, 10);

    int valid = errno != ERANGE &&
                end != token &&
                *end == '\0' &&
                parsed <= SIZE_MAX;

    free(token);

    if (!valid) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int input_has_only_whitespace(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        if (!isspace((unsigned char)ch)) {
            return 0;
        }
    }

    return !ferror(stdin);
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

static int find_maximum_sum(int64_t *const *triangle,
                            size_t rows,
                            int64_t *result)
{
    if (triangle == NULL || result == NULL || rows == 0 ||
        rows > SIZE_MAX / sizeof(int64_t)) {
        return -1;
    }

    for (size_t row = 0; row < rows; ++row) {
        if (triangle[row] == NULL) {
            return -1;
        }
    }

    int64_t *sums = malloc(rows * sizeof(*sums));
    if (sums == NULL) {
        return -1;
    }

    for (size_t col = 0; col < rows; ++col) {
        sums[col] = triangle[rows - 1][col];
    }

    for (size_t row = rows - 1; row > 0; --row) {
        for (size_t col = 0; col < row; ++col) {
            int64_t best = sums[col] > sums[col + 1]
                               ? sums[col]
                               : sums[col + 1];

            if (add_int64_checked(triangle[row - 1][col],
                                  best,
                                  &sums[col]) != 0) {
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