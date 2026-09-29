#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    MAX_SUM_SUCCESS,
    MAX_SUM_INVALID_ARGUMENT,
    MAX_SUM_OVERFLOW
} MaxSumStatus;

typedef struct {
    FILE *stream;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];
    size_t position;
    size_t length;
    bool end_of_file;
    bool error;
} InputScanner;

static bool input_scanner_init(InputScanner *scanner, FILE *stream)
{
    if (scanner == NULL || stream == NULL) {
        return false;
    }

    scanner->stream = stream;
    scanner->position = 0;
    scanner->length = 0;
    scanner->end_of_file = false;
    scanner->error = false;

    return true;
}

static bool input_scanner_get(InputScanner *scanner, int *result)
{
    if (scanner == NULL || result == NULL || scanner->stream == NULL ||
        scanner->end_of_file || scanner->error) {
        return false;
    }

    if (scanner->position == scanner->length) {
        scanner->length = fread(
            scanner->buffer,
            sizeof(scanner->buffer[0]),
            sizeof(scanner->buffer) / sizeof(scanner->buffer[0]),
            scanner->stream);
        scanner->position = 0;

        if (scanner->length == 0) {
            if (ferror(scanner->stream) != 0) {
                scanner->error = true;
            } else {
                scanner->end_of_file = true;
            }

            return false;
        }
    }

    *result = (int)scanner->buffer[scanner->position++];
    return true;
}

static bool is_input_space(int c)
{
    return c == ' ' || c == '\t' || c == '\n' ||
           c == '\r' || c == '\f' || c == '\v';
}

static bool read_size_value(InputScanner *scanner, size_t *result)
{
    size_t value = 0;
    int c;

    if (scanner == NULL || result == NULL) {
        return false;
    }

    do {
        if (!input_scanner_get(scanner, &c)) {
            return false;
        }
    } while (is_input_space(c));

    if (c == '+') {
        if (!input_scanner_get(scanner, &c)) {
            return false;
        }
    } else if (c == '-') {
        return false;
    }

    if (c < '0' || c > '9') {
        return false;
    }

    for (;;) {
        size_t digit = (size_t)(c - '0');

        if (value > (SIZE_MAX - digit) / (size_t)10) {
            return false;
        }

        value = value * (size_t)10 + digit;

        if (!input_scanner_get(scanner, &c)) {
            if (scanner->error) {
                return false;
            }

            *result = value;
            return true;
        }

        if (c < '0' || c > '9') {
            if (!is_input_space(c)) {
                return false;
            }

            *result = value;
            return true;
        }
    }
}

static bool read_int64_value(InputScanner *scanner, int64_t *result)
{
    uint64_t magnitude = 0;
    uint64_t limit;
    bool negative = false;
    int c;

    if (scanner == NULL || result == NULL) {
        return false;
    }

    do {
        if (!input_scanner_get(scanner, &c)) {
            return false;
        }
    } while (is_input_space(c));

    if (c == '+' || c == '-') {
        negative = c == '-';

        if (!input_scanner_get(scanner, &c)) {
            return false;
        }
    }

    if (c < '0' || c > '9') {
        return false;
    }

    limit = negative
        ? (uint64_t)INT64_MAX + UINT64_C(1)
        : (uint64_t)INT64_MAX;

    for (;;) {
        uint64_t digit = (uint64_t)(c - '0');

        if (magnitude > (limit - digit) / UINT64_C(10)) {
            return false;
        }

        magnitude = magnitude * UINT64_C(10) + digit;

        if (!input_scanner_get(scanner, &c)) {
            if (scanner->error) {
                return false;
            }

            break;
        }

        if (c < '0' || c > '9') {
            if (!is_input_space(c)) {
                return false;
            }

            break;
        }
    }

    if (negative) {
        if (magnitude == (uint64_t)INT64_MAX + UINT64_C(1)) {
            *result = INT64_MIN;
        } else {
            *result = -(int64_t)magnitude;
        }
    } else {
        *result = (int64_t)magnitude;
    }

    return true;
}

static bool checked_add_int64(int64_t lhs, int64_t rhs, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if ((rhs > 0 && lhs > INT64_MAX - rhs) ||
        (rhs < 0 && lhs < INT64_MIN - rhs)) {
        return false;
    }

    *result = lhs + rhs;
    return true;
}

static MaxSumStatus max_sum_without_three_consecutive(
    const int64_t *values,
    size_t count,
    int64_t *result)
{
    int64_t zero = 0;
    int64_t one = 0;
    int64_t two = 0;
    bool one_valid = false;
    bool two_valid = false;

    if (result == NULL || (count != 0 && values == NULL)) {
        return MAX_SUM_INVALID_ARGUMENT;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t next_zero = zero;
        int64_t next_one;
        int64_t next_two = 0;
        bool next_one_valid;
        bool next_two_valid = false;

        if (one_valid && one > next_zero) {
            next_zero = one;
        }

        if (two_valid && two > next_zero) {
            next_zero = two;
        }

        if (!checked_add_int64(zero, values[i], &next_one)) {
            return MAX_SUM_OVERFLOW;
        }

        next_one_valid = next_one >= 0;

        if (one_valid) {
            if (!checked_add_int64(one, values[i], &next_two)) {
                return MAX_SUM_OVERFLOW;
            }

            next_two_valid = next_two >= 0;
        }

        zero = next_zero;
        one = next_one;
        two = next_two;
        one_valid = next_one_valid;
        two_valid = next_two_valid;
    }

    *result = zero;

    if (one_valid && one > *result) {
        *result = one;
    }

    if (two_valid && two > *result) {
        *result = two;
    }

    return MAX_SUM_SUCCESS;
}

int main(void)
{
    InputScanner scanner;
    size_t count;
    int64_t *values = NULL;
    int64_t result;
    MaxSumStatus status;

    if (!input_scanner_init(&scanner, stdin)) {
        fputs("Failed to initialize input scanner.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_size_value(&scanner, &count)) {
        fputs("Failed to read the number of elements.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Input size is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0) {
        values = malloc(count * sizeof(*values));

        if (values == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int64_value(&scanner, &values[i])) {
            fprintf(stderr, "Failed to read element %zu.\n", i);
            free(values);
            return EXIT_FAILURE;
        }
    }

    status = max_sum_without_three_consecutive(values, count, &result);
    free(values);

    switch (status) {
        case MAX_SUM_SUCCESS:
            break;

        case MAX_SUM_INVALID_ARGUMENT:
            fputs("Invalid argument.\n", stderr);
            return EXIT_FAILURE;

        case MAX_SUM_OVERFLOW:
            fputs("The maximum sum exceeds the supported range.\n", stderr);
            return EXIT_FAILURE;

        default:
            fputs("Unexpected processing error.\n", stderr);
            return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0 || fflush(stdout) == EOF) {
        fputs("Failed to write the result.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}