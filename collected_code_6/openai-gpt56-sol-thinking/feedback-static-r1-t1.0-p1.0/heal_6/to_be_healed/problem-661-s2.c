#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    FILE *stream;
    bool error;
} InputScanner;

typedef struct {
    int64_t ending_with_zero;
    int64_t ending_with_one;
    int64_t ending_with_two;
    bool one_valid;
    bool two_valid;
} MaxSumState;

static bool scanner_init(InputScanner *scanner, FILE *stream)
{
    if (scanner == NULL || stream == NULL) {
        return false;
    }

    scanner->stream = stream;
    scanner->error = false;

    return true;
}

static int scanner_get(InputScanner *scanner)
{
    int ch;

    if (scanner == NULL || scanner->stream == NULL || scanner->error) {
        return EOF;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ch = fgetc(scanner->stream);

    if (ch == EOF && ferror(scanner->stream)) {
        scanner->error = true;
    }

    return ch;
}

static bool scanner_has_error(const InputScanner *scanner)
{
    return scanner == NULL ||
           scanner->stream == NULL ||
           scanner->error;
}

static int scanner_next_nonspace(InputScanner *scanner)
{
    int ch;

    do {
        ch = scanner_get(scanner);
    } while (ch != EOF && isspace((unsigned char)ch));

    return ch;
}

static bool read_size_value(InputScanner *scanner, size_t *value)
{
    size_t parsed = 0;
    bool valid = true;
    bool have_digit = false;
    int ch;

    if (scanner == NULL || scanner->stream == NULL || value == NULL) {
        return false;
    }

    ch = scanner_next_nonspace(scanner);
    if (ch == EOF) {
        return false;
    }

    if (ch == '+' || ch == '-') {
        if (ch == '-') {
            valid = false;
        }

        ch = scanner_get(scanner);
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (!isdigit((unsigned char)ch)) {
            valid = false;
        } else {
            unsigned int digit = (unsigned int)(ch - '0');

            have_digit = true;

            if (valid) {
                if (parsed > (SIZE_MAX - digit) / (size_t)10) {
                    valid = false;
                } else {
                    parsed = parsed * (size_t)10 + (size_t)digit;
                }
            }
        }

        ch = scanner_get(scanner);
    }

    if (scanner_has_error(scanner) || !valid || !have_digit) {
        return false;
    }

    *value = parsed;
    return true;
}

static bool read_int64_value(InputScanner *scanner, int64_t *value)
{
    uintmax_t parsed = 0;
    uintmax_t limit;
    bool negative = false;
    bool valid = true;
    bool have_digit = false;
    int ch;

    if (scanner == NULL || scanner->stream == NULL || value == NULL) {
        return false;
    }

    ch = scanner_next_nonspace(scanner);
    if (ch == EOF) {
        return false;
    }

    if (ch == '+' || ch == '-') {
        negative = ch == '-';
        ch = scanner_get(scanner);
    }

    limit = negative
                ? (uintmax_t)INT64_MAX + UINTMAX_C(1)
                : (uintmax_t)INT64_MAX;

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (!isdigit((unsigned char)ch)) {
            valid = false;
        } else {
            unsigned int digit = (unsigned int)(ch - '0');

            have_digit = true;

            if (valid) {
                if (parsed > (limit - digit) / UINTMAX_C(10)) {
                    valid = false;
                } else {
                    parsed = parsed * UINTMAX_C(10) + digit;
                }
            }
        }

        ch = scanner_get(scanner);
    }

    if (scanner_has_error(scanner) || !valid || !have_digit) {
        return false;
    }

    if (negative) {
        if (parsed == (uintmax_t)INT64_MAX + UINTMAX_C(1)) {
            *value = INT64_MIN;
        } else {
            *value = -(int64_t)parsed;
        }
    } else {
        *value = (int64_t)parsed;
    }

    return true;
}

static int checked_add_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return 1;
    }

    if (right > 0 && left > INT64_MAX - right) {
        return 1;
    }

    if (right < 0 && left < INT64_MIN - right) {
        return -1;
    }

    *result = left + right;
    return 0;
}

static bool max_sum_init(MaxSumState *state)
{
    if (state == NULL) {
        return false;
    }

    state->ending_with_zero = 0;
    state->ending_with_one = 0;
    state->ending_with_two = 0;
    state->one_valid = false;
    state->two_valid = false;

    return true;
}

static bool max_sum_add(MaxSumState *state, int64_t value)
{
    int64_t new_zero;
    int64_t new_one;
    int64_t new_two = 0;
    bool new_two_valid = false;
    int status;

    if (state == NULL) {
        return false;
    }

    new_zero = state->ending_with_zero;

    if (state->one_valid && state->ending_with_one > new_zero) {
        new_zero = state->ending_with_one;
    }

    if (state->two_valid && state->ending_with_two > new_zero) {
        new_zero = state->ending_with_two;
    }

    status = checked_add_int64(state->ending_with_zero,
                               value,
                               &new_one);
    if (status != 0) {
        return false;
    }

    if (state->one_valid) {
        status = checked_add_int64(state->ending_with_one,
                                   value,
                                   &new_two);

        if (status > 0) {
            return false;
        }

        new_two_valid = status == 0;
    }

    state->ending_with_zero = new_zero;
    state->ending_with_one = new_one;
    state->ending_with_two = new_two;
    state->one_valid = true;
    state->two_valid = new_two_valid;

    return true;
}

static bool max_sum_result(const MaxSumState *state, int64_t *result)
{
    if (state == NULL || result == NULL) {
        return false;
    }

    *result = state->ending_with_zero;

    if (state->one_valid && state->ending_with_one > *result) {
        *result = state->ending_with_one;
    }

    if (state->two_valid && state->ending_with_two > *result) {
        *result = state->ending_with_two;
    }

    return true;
}

int main(void)
{
    InputScanner scanner;
    MaxSumState state;
    size_t count;
    int64_t value;
    int64_t result;

    if (!scanner_init(&scanner, stdin)) {
        fputs("Scanner initialization failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_size_value(&scanner, &count)) {
        fputs("Invalid element count\n", stderr);
        return EXIT_FAILURE;
    }

    if (!max_sum_init(&state)) {
        fputs("Unable to initialize computation\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int64_value(&scanner, &value)) {
            fputs("Invalid element\n", stderr);
            return EXIT_FAILURE;
        }

        if (!max_sum_add(&state, value)) {
            fputs("Unable to compute the result\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (!max_sum_result(&state, &result)) {
        fputs("Unable to compute the result\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}