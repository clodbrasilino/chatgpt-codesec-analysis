#include <ctype.h>
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

static void input_scanner_init(InputScanner *scanner, FILE *stream)
{
    if (scanner == NULL) {
        return;
    }

    scanner->stream = stream;
    scanner->position = 0;
    scanner->length = 0;
    scanner->end_of_file = false;
    scanner->error = false;
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
            sizeof(scanner->buffer),
            scanner->stream);
        scanner->position = 0;

        if (scanner->length == 0) {
            if (ferror(scanner->stream)) {
                scanner->error = true;
            } else {
                scanner->end_of_file = true;
            }

            return false;
        }
    }

    *result = scanner->buffer[scanner->position];
    ++scanner->position;
    return true;
}

static bool read_size_value(InputScanner *scanner, size_t *result)
{
    uintmax_t value = 0;
    const uintmax_t limit = (uintmax_t)SIZE_MAX;
    int c;

    if (scanner == NULL || result == NULL) {
        return false;
    }

    do {
        if (!input_scanner_get(scanner, &c)) {
            return false;
        }
    } while (isspace((unsigned char)c));

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

    do {
        unsigned int digit = (unsigned int)(c - '0');

        if (value > (limit - digit) / UINTMAX_C(10)) {
            return false;
        }

        value = value * UINTMAX_C(10) + digit;

        if (!input_scanner_get(scanner, &c)) {
            if (scanner->error) {
                return false;
            }

            *result = (size_t)value;
            return true;
        }
    } while (c >= '0' && c <= '9');

    if (!isspace((unsigned char)c)) {
        return false;
    }

    *result = (size_t)value;
    return true;
}

static bool read_int64_value(InputScanner *scanner, int64_t *result)
{
    uintmax_t magnitude = 0;
    uintmax_t limit;
    bool negative = false;
    int c;

    if (scanner == NULL || result == NULL) {
        return false;
    }

    do {
        if (!input_scanner_get(scanner, &c)) {
            return false;
        }
    } while (isspace((unsigned char)c));

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
        ? (uintmax_t)INT64_MAX + UINTMAX_C(1)
        : (uintmax_t)INT64_MAX;

    do {
        unsigned int digit = (unsigned int)(c - '0');

        if (magnitude > (limit - digit) / UINTMAX_C(10)) {
            return false;
        }

        magnitude = magnitude * UINTMAX_C(10) + digit;

        if (!input_scanner_get(scanner, &c)) {
            if (scanner->error) {
                return false;
            }

            break;
        }

        if (c < '0' || c > '9') {
            if (!isspace((unsigned char)c)) {
                return false;
            }

            break;
        }
    } while (true);

    if (negative) {
        if (magnitude == (uintmax_t)INT64_MAX + UINTMAX_C(1)) {
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

    input_scanner_init(&scanner, stdin);

    if (!read_size_value(&scanner, &count)) {
        fprintf(stderr, "Failed to read the number of elements.\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Input size is too large.\n");
        return EXIT_FAILURE;
    }

    if (count != 0) {
        values = malloc(count * sizeof(*values));

        if (values == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
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

    if (status == MAX_SUM_INVALID_ARGUMENT) {
        fprintf(stderr, "Invalid argument.\n");
        return EXIT_FAILURE;
    }

    if (status == MAX_SUM_OVERFLOW) {
        fprintf(stderr, "The maximum sum exceeds the supported range.\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        fprintf(stderr, "Failed to write the result.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}