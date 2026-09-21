#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    FILE *stream;
    int error;
} InputStream;

static int input_get(InputStream *input)
{
    int ch = fgetc(input->stream);

    if (ch == EOF && ferror(input->stream)) {
        input->error = 1;
    }

    return ch;
}

static int read_first_nonspace(InputStream *input, int *character)
{
    int ch;

    do {
        ch = input_get(input);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    *character = ch;
    return 1;
}

static int read_decimal(InputStream *input,
                        uintmax_t positive_limit,
                        uintmax_t negative_limit,
                        int allow_negative,
                        uintmax_t *magnitude,
                        int *is_negative)
{
    int ch;
    int negative = 0;
    int has_digit = 0;
    int valid = 1;
    int overflow = 0;
    uintmax_t result = 0;
    uintmax_t limit;

    if (!read_first_nonspace(input, &ch)) {
        return 0;
    }

    if (ch == '+' || ch == '-') {
        negative = ch == '-';

        if (negative && !allow_negative) {
            valid = 0;
        }

        ch = input_get(input);
    }

    limit = negative ? negative_limit : positive_limit;

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (ch >= '0' && ch <= '9') {
            uintmax_t digit = (uintmax_t)(ch - '0');

            has_digit = 1;

            if (!overflow) {
                if (result > limit / UINTMAX_C(10) ||
                    (result == limit / UINTMAX_C(10) &&
                     digit > limit % UINTMAX_C(10))) {
                    overflow = 1;
                } else {
                    result = result * UINTMAX_C(10) + digit;
                }
            }
        } else {
            valid = 0;
        }

        ch = input_get(input);
    }

    if (input->error || !valid || !has_digit || overflow) {
        return 0;
    }

    *magnitude = result;
    *is_negative = negative;
    return 1;
}

static int read_size(InputStream *input, size_t *value)
{
    uintmax_t magnitude;
    int negative;

    if (!read_decimal(input, (uintmax_t)SIZE_MAX, UINTMAX_C(0), 0,
                      &magnitude, &negative)) {
        return 0;
    }

    *value = (size_t)magnitude;
    return 1;
}

static int read_integer(InputStream *input, int *value)
{
    uintmax_t magnitude;
    uintmax_t negative_limit =
        (uintmax_t)(-(INT_MIN + 1)) + UINTMAX_C(1);
    int negative;

    if (!read_decimal(input, (uintmax_t)INT_MAX, negative_limit, 1,
                      &magnitude, &negative)) {
        return 0;
    }

    if (negative) {
        if (magnitude == negative_limit) {
            *value = INT_MIN;
        } else {
            *value = -(int)magnitude;
        }
    } else {
        *value = (int)magnitude;
    }

    return 1;
}

static size_t remove_duplicate_numbers(int *values, size_t count)
{
    size_t unique_count = 0;

    for (size_t i = 0; i < count; ++i) {
        size_t j = 0;

        while (j < unique_count && values[j] != values[i]) {
            ++j;
        }

        if (j == unique_count) {
            values[unique_count] = values[i];
            ++unique_count;
        }
    }

    return unique_count;
}

static int print_list(const int *values, size_t count)
{
    for (size_t i = 0; i < count; ++i) {
        if (i != 0 && fputc(' ', stdout) == EOF) {
            return 0;
        }

        if (fprintf(stdout, "%d", values[i]) < 0) {
            return 0;
        }
    }

    return fputc('\n', stdout) != EOF;
}

int main(void)
{
    InputStream input = {stdin, 0};
    size_t list_count;

    if (!read_size(&input, &list_count)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t list_index = 0; list_index < list_count; ++list_index) {
        size_t count;
        size_t unique_count;
        int *values = NULL;

        if (!read_size(&input, &count)) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        if (count > SIZE_MAX / sizeof(*values)) {
            fputs("List is too large\n", stderr);
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
            if (!read_integer(&input, &values[i])) {
                free(values);
                fputs("Invalid input\n", stderr);
                return EXIT_FAILURE;
            }
        }

        unique_count = remove_duplicate_numbers(values, count);

        if (!print_list(values, unique_count)) {
            free(values);
            fputs("Output error\n", stderr);
            return EXIT_FAILURE;
        }

        free(values);
    }

    if (fflush(stdout) == EOF) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}