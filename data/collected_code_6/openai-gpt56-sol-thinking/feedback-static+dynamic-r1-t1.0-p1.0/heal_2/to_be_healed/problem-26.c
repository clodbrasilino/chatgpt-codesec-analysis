#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <ctype.h>

typedef struct {
    int *elements;
    size_t count;
} Tuple;

static bool read_magnitude(FILE *stream,
                           bool allow_negative,
                           uintmax_t positive_limit,
                           uintmax_t negative_limit,
                           bool *negative,
                           uintmax_t *magnitude)
{
    int c;
    bool is_negative = false;
    bool have_digit = false;
    bool valid = true;
    bool overflow = false;
    uintmax_t result = 0;
    uintmax_t limit;

    if (stream == NULL || negative == NULL || magnitude == NULL) {
        return false;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = fgetc(stream);
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF) {
        return false;
    }

    if (c == '+' || c == '-') {
        is_negative = c == '-';
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = fgetc(stream);
    }

    limit = is_negative ? negative_limit : positive_limit;

    while (c != EOF && !isspace((unsigned char)c)) {
        if (c < '0' || c > '9') {
            valid = false;
        } else {
            unsigned int digit = (unsigned int)(c - '0');

            have_digit = true;

            if (!overflow) {
                if (result > limit / 10 ||
                    (result == limit / 10 &&
                     (uintmax_t)digit > limit % 10)) {
                    overflow = true;
                } else {
                    result = result * 10 + digit;
                }
            }
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = fgetc(stream);
    }

    if (c == EOF && ferror(stream)) {
        return false;
    }

    if (!have_digit || !valid || overflow ||
        (is_negative && !allow_negative)) {
        return false;
    }

    *negative = is_negative;
    *magnitude = result;
    return true;
}

static bool read_size(FILE *stream, size_t *value)
{
    bool negative;
    uintmax_t magnitude;

    if (value == NULL ||
        !read_magnitude(stream, false, SIZE_MAX, SIZE_MAX,
                        &negative, &magnitude)) {
        return false;
    }

    *value = (size_t)magnitude;
    return true;
}

static bool read_int(FILE *stream, int *value)
{
    bool negative;
    uintmax_t magnitude;
    const uintmax_t positive_limit = (uintmax_t)INT_MAX;
    const uintmax_t negative_limit =
        (uintmax_t)(-(INT_MIN + 1)) + UINTMAX_C(1);

    if (value == NULL ||
        !read_magnitude(stream, true, positive_limit, negative_limit,
                        &negative, &magnitude)) {
        return false;
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

    return true;
}

static bool tuple_list_has_all_k(const Tuple *tuples,
                                 size_t tuple_count,
                                 int k)
{
    size_t i;
    size_t j;

    if (tuples == NULL && tuple_count != 0) {
        return false;
    }

    for (i = 0; i < tuple_count; ++i) {
        bool found = false;

        if (tuples[i].elements == NULL && tuples[i].count != 0) {
            return false;
        }

        for (j = 0; j < tuples[i].count; ++j) {
            if (tuples[i].elements[j] == k) {
                found = true;
                break;
            }
        }

        if (!found) {
            return false;
        }
    }

    return true;
}

static void free_tuples(Tuple *tuples, size_t tuple_count)
{
    size_t i;

    if (tuples == NULL) {
        return;
    }

    for (i = 0; i < tuple_count; ++i) {
        free(tuples[i].elements);
    }

    free(tuples);
}

int main(void)
{
    Tuple *tuples = NULL;
    size_t tuple_count;
    size_t i;
    size_t j;
    int k;
    bool result;

    if (!read_size(stdin, &tuple_count) || !read_int(stdin, &k)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (tuple_count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Tuple count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (tuple_count != 0) {
        tuples = calloc(tuple_count, sizeof(*tuples));
        if (tuples == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < tuple_count; ++i) {
        if (!read_size(stdin, &tuples[i].count)) {
            fputs("Invalid tuple size\n", stderr);
            free_tuples(tuples, tuple_count);
            return EXIT_FAILURE;
        }

        if (tuples[i].count >
            SIZE_MAX / sizeof(*tuples[i].elements)) {
            fputs("Tuple size is too large\n", stderr);
            free_tuples(tuples, tuple_count);
            return EXIT_FAILURE;
        }

        if (tuples[i].count != 0) {
            tuples[i].elements =
                malloc(tuples[i].count * sizeof(*tuples[i].elements));

            if (tuples[i].elements == NULL) {
                fputs("Memory allocation failed\n", stderr);
                free_tuples(tuples, tuple_count);
                return EXIT_FAILURE;
            }
        }

        for (j = 0; j < tuples[i].count; ++j) {
            if (!read_int(stdin, &tuples[i].elements[j])) {
                fputs("Invalid tuple element\n", stderr);
                free_tuples(tuples, tuple_count);
                return EXIT_FAILURE;
            }
        }
    }

    result = tuple_list_has_all_k(tuples, tuple_count, k);
    free_tuples(tuples, tuple_count);

    if (puts(result ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}