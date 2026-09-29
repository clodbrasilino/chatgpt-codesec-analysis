#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    INPUT_SUCCESS,
    INPUT_INVALID,
    INPUT_OUT_OF_RANGE
} InputStatus;

typedef enum {
    MAX_SUM_SUCCESS,
    MAX_SUM_INVALID_ARGUMENT,
    MAX_SUM_OVERFLOW
} MaxSumStatus;

static InputStatus read_size_value(FILE *stream, size_t *value)
{
    uintmax_t magnitude = 0;
    const uintmax_t limit = (uintmax_t)SIZE_MAX;
    int ch;

    if (stream == NULL || value == NULL) {
        return INPUT_INVALID;
    }

    do {
        ch = fgetc(stream);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return INPUT_INVALID;
    }

    if (ch == '+') {
        ch = fgetc(stream);
    } else if (ch == '-') {
        return INPUT_INVALID;
    }

    if (ch == EOF || ch < '0' || ch > '9') {
        return INPUT_INVALID;
    }

    do {
        uintmax_t digit = (uintmax_t)(ch - '0');

        if (magnitude > (limit - digit) / UINTMAX_C(10)) {
            return INPUT_OUT_OF_RANGE;
        }

        magnitude = magnitude * UINTMAX_C(10) + digit;
        ch = fgetc(stream);
    } while (ch != EOF && ch >= '0' && ch <= '9');

    if (ch != EOF && !isspace((unsigned char)ch)) {
        return INPUT_INVALID;
    }

    if (ch == EOF && ferror(stream)) {
        return INPUT_INVALID;
    }

    *value = (size_t)magnitude;
    return INPUT_SUCCESS;
}

static InputStatus read_int64_value(FILE *stream, int64_t *value)
{
    uintmax_t magnitude = 0;
    uintmax_t limit;
    bool negative = false;
    int ch;

    if (stream == NULL || value == NULL) {
        return INPUT_INVALID;
    }

    do {
        ch = fgetc(stream);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return INPUT_INVALID;
    }

    if (ch == '+' || ch == '-') {
        negative = ch == '-';
        ch = fgetc(stream);
    }

    if (ch == EOF || ch < '0' || ch > '9') {
        return INPUT_INVALID;
    }

    limit = negative
        ? (uintmax_t)INT64_MAX + UINTMAX_C(1)
        : (uintmax_t)INT64_MAX;

    do {
        uintmax_t digit = (uintmax_t)(ch - '0');

        if (magnitude > (limit - digit) / UINTMAX_C(10)) {
            return INPUT_OUT_OF_RANGE;
        }

        magnitude = magnitude * UINTMAX_C(10) + digit;
        ch = fgetc(stream);
    } while (ch != EOF && ch >= '0' && ch <= '9');

    if (ch != EOF && !isspace((unsigned char)ch)) {
        return INPUT_INVALID;
    }

    if (ch == EOF && ferror(stream)) {
        return INPUT_INVALID;
    }

    if (negative) {
        if (magnitude == (uintmax_t)INT64_MAX + UINTMAX_C(1)) {
            *value = INT64_MIN;
        } else {
            *value = -(int64_t)magnitude;
        }
    } else {
        *value = (int64_t)magnitude;
    }

    return INPUT_SUCCESS;
}

static bool checked_add(int64_t lhs, int64_t rhs, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if (rhs > 0 && lhs > INT64_MAX - rhs) {
        return false;
    }

    if (rhs < 0 && lhs < INT64_MIN - rhs) {
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

    if (result == NULL || (count > 0 && values == NULL)) {
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

        if (!checked_add(zero, values[i], &next_one)) {
            return MAX_SUM_OVERFLOW;
        }

        next_one_valid = next_one >= 0;

        if (one_valid) {
            if (!checked_add(one, values[i], &next_two)) {
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
    size_t count;
    int64_t *values = NULL;
    int64_t result;
    InputStatus input_status;
    MaxSumStatus max_sum_status;

    input_status = read_size_value(stdin, &count);

    if (input_status == INPUT_OUT_OF_RANGE) {
        fprintf(stderr, "The number of elements is too large.\n");
        return EXIT_FAILURE;
    }

    if (input_status != INPUT_SUCCESS) {
        fprintf(stderr, "Failed to read the number of elements.\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Input size is too large.\n");
        return EXIT_FAILURE;
    }

    if (count > 0) {
        values = malloc(count * sizeof(*values));

        if (values == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        input_status = read_int64_value(stdin, &values[i]);

        if (input_status == INPUT_OUT_OF_RANGE) {
            fprintf(stderr, "Element %zu is outside the supported range.\n", i);
            free(values);
            return EXIT_FAILURE;
        }

        if (input_status != INPUT_SUCCESS) {
            fprintf(stderr, "Failed to read element %zu.\n", i);
            free(values);
            return EXIT_FAILURE;
        }
    }

    max_sum_status =
        max_sum_without_three_consecutive(values, count, &result);

    free(values);

    if (max_sum_status == MAX_SUM_INVALID_ARGUMENT) {
        fprintf(stderr, "Invalid argument.\n");
        return EXIT_FAILURE;
    }

    if (max_sum_status == MAX_SUM_OVERFLOW) {
        fprintf(stderr, "The maximum sum exceeds the supported range.\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        fprintf(stderr, "Failed to write the result.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}