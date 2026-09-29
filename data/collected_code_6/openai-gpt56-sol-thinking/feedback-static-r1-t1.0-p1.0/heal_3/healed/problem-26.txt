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

typedef struct {
    FILE *stream;
    bool error;
} InputReader;

static void input_reader_init(InputReader *reader, FILE *stream)
{
    if (reader != NULL) {
        reader->stream = stream;
        reader->error = false;
    }
}

static int input_reader_get(InputReader *reader)
{
    int c;

    if (reader == NULL || reader->stream == NULL || reader->error) {
        return EOF;
    }

    c = fgetc(reader->stream);

    if (c == EOF && ferror(reader->stream)) {
        reader->error = true;
    }

    return c;
}

static bool read_decimal_token(
    InputReader *reader,
    bool *negative,
    uintmax_t *value
)
{
    int c;
    bool token_negative = false;
    bool has_digit = false;
    bool valid = true;
    bool overflow = false;
    uintmax_t result = 0;

    if (reader == NULL || negative == NULL || value == NULL) {
        return false;
    }

    do {
        c = input_reader_get(reader);
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF) {
        return false;
    }

    if (c == '+' || c == '-') {
        token_negative = c == '-';
        c = input_reader_get(reader);
    }

    while (c != EOF && !isspace((unsigned char)c)) {
        if (c >= '0' && c <= '9') {
            uintmax_t digit = (uintmax_t)(c - '0');

            has_digit = true;

            if (!overflow) {
                if (result > (UINTMAX_MAX - digit) / UINTMAX_C(10)) {
                    overflow = true;
                } else {
                    result = result * UINTMAX_C(10) + digit;
                }
            }
        } else {
            valid = false;
        }

        c = input_reader_get(reader);
    }

    if (reader->error || !has_digit || !valid || overflow) {
        return false;
    }

    *negative = token_negative;
    *value = result;

    return true;
}

static bool read_size(InputReader *reader, size_t *value)
{
    bool negative;
    uintmax_t parsed;

    if (value == NULL ||
        !read_decimal_token(reader, &negative, &parsed) ||
        negative ||
        parsed > (uintmax_t)SIZE_MAX) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

static bool read_int(InputReader *reader, int *value)
{
    bool negative;
    uintmax_t parsed;
    const uintmax_t negative_limit =
        (uintmax_t)INT_MAX + UINTMAX_C(1);

    if (value == NULL ||
        !read_decimal_token(reader, &negative, &parsed)) {
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

static bool tuple_list_has_all_k(
    const Tuple *tuples,
    size_t tuple_count,
    int k
)
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
    InputReader reader;
    Tuple *tuples = NULL;
    size_t tuple_count;
    size_t i;
    size_t j;
    int k;
    bool result;

    input_reader_init(&reader, stdin);

    if (!read_size(&reader, &tuple_count) ||
        !read_int(&reader, &k)) {
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
        if (!read_size(&reader, &tuples[i].count)) {
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
            if (!read_int(&reader, &tuples[i].elements[j])) {
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