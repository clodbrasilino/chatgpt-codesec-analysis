#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_first_nonspace(int *character)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    *character = ch;
    return 1;
}

static int read_decimal(uintmax_t positive_limit,
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

    if (!read_first_nonspace(&ch)) {
        return 0;
    }

    if (ch == '+' || ch == '-') {
        negative = ch == '-';

        if (negative && !allow_negative) {
            valid = 0;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    limit = negative ? negative_limit : positive_limit;

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (ch >= '0' && ch <= '9') {
            uintmax_t digit = (uintmax_t)(ch - '0');

            has_digit = 1;

            if (!overflow) {
                if (result > limit / 10 ||
                    (result == limit / 10 && digit > limit % 10)) {
                    overflow = 1;
                } else {
                    result = result * 10 + digit;
                }
            }
        } else {
            valid = 0;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        return 0;
    }

    if (!valid || !has_digit || overflow) {
        return 0;
    }

    *magnitude = result;
    *is_negative = negative;
    return 1;
}

static int read_size(size_t *value)
{
    uintmax_t magnitude;
    int negative;

    if (!read_decimal((uintmax_t)SIZE_MAX, 0, 0,
                      &magnitude, &negative)) {
        return 0;
    }

    *value = (size_t)magnitude;
    return 1;
}

static int read_integer(int *value)
{
    uintmax_t magnitude;
    uintmax_t negative_limit =
        (uintmax_t)(-(INT_MIN + 1)) + UINTMAX_C(1);
    int negative;

    if (!read_decimal((uintmax_t)INT_MAX, negative_limit, 1,
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
        size_t j;

        for (j = 0; j < unique_count; ++j) {
            if (values[j] == values[i]) {
                break;
            }
        }

        if (j == unique_count) {
            values[unique_count++] = values[i];
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
    size_t list_count;

    if (!read_size(&list_count)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t list_index = 0; list_index < list_count; ++list_index) {
        size_t count;
        size_t unique_count;
        int *values = NULL;

        if (!read_size(&count)) {
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
            if (!read_integer(&values[i])) {
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