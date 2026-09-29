#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    FILE *stream;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];
    size_t position;
    size_t length;
} InputScanner;

static void scanner_init(InputScanner *scanner, FILE *stream)
{
    scanner->stream = stream;
    scanner->position = 0;
    scanner->length = 0;
}

static int scanner_get(InputScanner *scanner)
{
    if (scanner->position == scanner->length) {
        scanner->length = fread(scanner->buffer,
                                1,
                                sizeof(scanner->buffer),
                                scanner->stream);
        scanner->position = 0;

        if (scanner->length == 0) {
            return EOF;
        }
    }

    return scanner->buffer[scanner->position++];
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

    if (scanner == NULL || value == NULL) {
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
                if (parsed > (SIZE_MAX - digit) / 10U) {
                    valid = false;
                } else {
                    parsed = parsed * 10U + digit;
                }
            }
        }

        ch = scanner_get(scanner);
    }

    if (ferror(scanner->stream) || !valid || !have_digit) {
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

    if (scanner == NULL || value == NULL) {
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

    if (ferror(scanner->stream) || !valid || !have_digit) {
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

static bool max_sum_no_three_consecutive(const int64_t *values,
                                         size_t count,
                                         int64_t *result)
{
    int64_t ending_with_zero = 0;
    int64_t ending_with_one = 0;
    int64_t ending_with_two = 0;
    bool one_valid = false;
    bool two_valid = false;

    if (result == NULL || (count != 0 && values == NULL)) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t new_zero = ending_with_zero;
        int64_t new_one;
        int64_t new_two = 0;
        bool new_two_valid = false;
        int status;

        if (one_valid && ending_with_one > new_zero) {
            new_zero = ending_with_one;
        }

        if (two_valid && ending_with_two > new_zero) {
            new_zero = ending_with_two;
        }

        status = checked_add_int64(ending_with_zero, values[i], &new_one);
        if (status != 0) {
            return false;
        }

        if (one_valid) {
            status = checked_add_int64(ending_with_one, values[i], &new_two);

            if (status > 0) {
                return false;
            }

            new_two_valid = status == 0;
        }

        ending_with_zero = new_zero;
        ending_with_one = new_one;
        ending_with_two = new_two;
        one_valid = true;
        two_valid = new_two_valid;
    }

    *result = ending_with_zero;

    if (one_valid && ending_with_one > *result) {
        *result = ending_with_one;
    }

    if (two_valid && ending_with_two > *result) {
        *result = ending_with_two;
    }

    return true;
}

int main(void)
{
    InputScanner scanner;
    size_t count;
    int64_t *values = NULL;
    int64_t result;

    scanner_init(&scanner, stdin);

    if (!read_size_value(&scanner, &count)) {
        fputs("Invalid element count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Element count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0) {
        values = malloc(count * sizeof(*values));

        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int64_value(&scanner, &values[i])) {
            fputs("Invalid element\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!max_sum_no_three_consecutive(values, count, &result)) {
        fputs("Unable to compute the result\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        fputs("Output error\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}