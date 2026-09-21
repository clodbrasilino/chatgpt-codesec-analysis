#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    TOKEN_OK = 1,
    TOKEN_EOF = 0,
    TOKEN_ERROR = -1,
    TOKEN_TOO_LONG = -2
};

static int read_token(char *buffer, size_t capacity)
{
    size_t length = 0;
    int ch;
    int too_long = 0;

    if (buffer == NULL || capacity < 2) {
        return TOKEN_ERROR;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == EOF) {
            buffer[0] = '\0';
            return ferror(stdin) ? TOKEN_ERROR : TOKEN_EOF;
        }
    } while (isspace((unsigned char)ch));

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length + 1 < capacity) {
            buffer[length++] = (char)ch;
        } else {
            too_long = 1;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    buffer[length] = '\0';

    if (ch == EOF && ferror(stdin)) {
        return TOKEN_ERROR;
    }

    return too_long ? TOKEN_TOO_LONG : TOKEN_OK;
}

static int read_size_value(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[sizeof(uintmax_t) * 3 + 3];
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_token(buffer, sizeof(buffer)) != TOKEN_OK) {
        return -1;
    }

    if (buffer[0] == '\0' || buffer[0] == '-' || buffer[0] == '+') {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_int64_value(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[sizeof(intmax_t) * 3 + 3];
    char *end;
    intmax_t parsed;

    if (value == NULL || read_token(buffer, sizeof(buffer)) != TOKEN_OK) {
        return -1;
    }

    if (buffer[0] == '\0') {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < (intmax_t)INT64_MIN || parsed > (intmax_t)INT64_MAX) {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

static int checked_multiply_int64(int64_t left, int64_t right,
                                  int64_t *result)
{
    if (result == NULL) {
        return -1;
    }

    if (left == 0 || right == 0) {
        *result = 0;
        return 0;
    }

    if ((left == -1 && right == INT64_MIN) ||
        (right == -1 && left == INT64_MIN)) {
        return -1;
    }

    if (left > 0) {
        if (right > 0) {
            if (left > INT64_MAX / right) {
                return -1;
            }
        } else if (right < INT64_MIN / left) {
            return -1;
        }
    } else {
        if (right > 0) {
            if (left < INT64_MIN / right) {
                return -1;
            }
        } else if (left < INT64_MAX / right) {
            return -1;
        }
    }

    *result = left * right;
    return 0;
}

static int multiply_kth_elements(const int64_t *tuples, size_t tuple_count,
                                 size_t tuple_size, size_t k,
                                 int64_t *product)
{
    int64_t result = 1;

    if (tuples == NULL || product == NULL || tuple_count == 0 ||
        tuple_size == 0 || k >= tuple_size ||
        tuple_count > SIZE_MAX / tuple_size) {
        return -1;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        int64_t next;

        if (checked_multiply_int64(result, tuples[i * tuple_size + k],
                                   &next) != 0) {
            return -2;
        }

        result = next;
    }

    *product = result;
    return 0;
}

int main(void)
{
    size_t tuple_count;
    size_t tuple_size;
    size_t k;
    size_t element_count;
    int64_t *tuples;
    int64_t product;
    int result;
    int status = EXIT_FAILURE;

    if (read_size_value(&tuple_count) != 0 ||
        read_size_value(&tuple_size) != 0 ||
        read_size_value(&k) != 0 ||
        tuple_count == 0 ||
        tuple_size == 0 ||
        k >= tuple_size ||
        tuple_count > SIZE_MAX / tuple_size) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    element_count = tuple_count * tuple_size;

    if (element_count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    tuples = malloc(element_count * sizeof(*tuples));
    if (tuples == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < element_count; ++i) {
        if (read_int64_value(&tuples[i]) != 0) {
            fputs("Invalid tuple data\n", stderr);
            goto cleanup;
        }
    }

    result = multiply_kth_elements(tuples, tuple_count, tuple_size, k,
                                   &product);

    if (result == -1) {
        fputs("Invalid arguments\n", stderr);
        goto cleanup;
    }

    if (result == -2) {
        fputs("Product overflow\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRId64 "\n", product) < 0) {
        fputs("Output error\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(tuples);
    return status;
}