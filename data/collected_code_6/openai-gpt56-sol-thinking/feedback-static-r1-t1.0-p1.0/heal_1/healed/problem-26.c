#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <ctype.h>

typedef struct {
    int *elements;
    size_t count;
} Tuple;

static bool read_decimal_token(FILE *stream, bool *negative, uintmax_t *value)
{
    int c;
    bool has_digit = false;
    bool valid = true;
    bool overflow = false;
    uintmax_t result = 0;

    if (stream == NULL || negative == NULL || value == NULL) {
        return false;
    }

    do {
        c = fgetc(stream);
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF) {
        return false;
    }

    *negative = false;

    if (c == '+' || c == '-') {
        *negative = (c == '-');
        c = fgetc(stream);
    }

    while (c != EOF && !isspace((unsigned char)c)) {
        if (c >= '0' && c <= '9') {
            uintmax_t digit = (uintmax_t)(c - '0');

            has_digit = true;

            if (!overflow) {
                if (result > (UINTMAX_MAX - digit) / 10) {
                    overflow = true;
                } else {
                    result = result * 10 + digit;
                }
            }
        } else {
            valid = false;
        }

        c = fgetc(stream);
    }

    if (c == EOF && ferror(stream)) {
        return false;
    }

    if (!has_digit || !valid || overflow) {
        return false;
    }

    *value = result;
    return true;
}

static bool read_size(FILE *stream, size_t *value)
{
    bool negative;
    uintmax_t parsed;

    if (value == NULL ||
        !read_decimal_token(stream, &negative, &parsed) ||
        negative ||
        parsed > SIZE_MAX) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

static bool read_int(FILE *stream, int *value)
{
    bool negative;
    uintmax_t parsed;
    uintmax_t negative_limit = (uintmax_t)INT_MAX + 1;

    if (value == NULL ||
        !read_decimal_token(stream, &negative, &parsed)) {
        return false;
    }

    if (negative) {
        if (parsed > negative_limit) {
            return false;
        }

        if (parsed == negative_limit) {
            *value = INT_MIN;
        } else {
            *value = -(int)parsed;
        }
    } else {
        if (parsed > (uintmax_t)INT_MAX) {
            return false;
        }

        *value = (int)parsed;
    }

    return true;
}

static bool tuple_list_has_all_k(const Tuple *tuples, size_t tuple_count, int k)
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

        if (tuples[i].count > SIZE_MAX / sizeof(*tuples[i].elements)) {
            fputs("Tuple size is too large\n", stderr);
            free_tuples(tuples, tuple_count);
            return EXIT_FAILURE;
        }

        if (tuples[i].count != 0) {
            tuples[i].elements = malloc(
                tuples[i].count * sizeof(*tuples[i].elements)
            );

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