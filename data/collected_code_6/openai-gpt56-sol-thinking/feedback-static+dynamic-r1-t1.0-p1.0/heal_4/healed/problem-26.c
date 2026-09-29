#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <ctype.h>

#define INPUT_BUFFER_SIZE 4096U
#define MAX_NUMERIC_DIGITS ((size_t)(sizeof(uintmax_t) * CHAR_BIT))

typedef struct {
    int *elements;
    size_t count;
} Tuple;

typedef struct {
    FILE *stream;
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t length;
    bool eof;
    bool error;
} Input;

static void input_init(Input *input, FILE *stream)
{
    if (input == NULL) {
        return;
    }

    input->stream = stream;
    input->position = 0;
    input->length = 0;
    input->eof = false;
    input->error = false;
}

static int input_get(Input *input)
{
    size_t bytes_read;

    if (input == NULL || input->stream == NULL ||
        input->eof || input->error) {
        return EOF;
    }

    if (input->position >= input->length) {
        bytes_read = fread(input->buffer, 1, sizeof(input->buffer),
                           input->stream);

        if (bytes_read == 0) {
            if (ferror(input->stream)) {
                input->error = true;
            } else {
                input->eof = true;
            }

            return EOF;
        }

        input->position = 0;
        input->length = bytes_read;
    }

    return (int)input->buffer[input->position++];
}

static bool read_magnitude(Input *input,
                           bool allow_negative,
                           uintmax_t positive_limit,
                           uintmax_t negative_limit,
                           bool *negative,
                           uintmax_t *magnitude)
{
    int c;
    bool is_negative = false;
    bool have_digit = false;
    uintmax_t result = 0;
    uintmax_t limit;
    size_t digit_count = 0;

    if (input == NULL || negative == NULL || magnitude == NULL) {
        return false;
    }

    do {
        c = input_get(input);
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF) {
        return false;
    }

    if (c == '+' || c == '-') {
        is_negative = c == '-';
        c = input_get(input);
    }

    if (is_negative && !allow_negative) {
        return false;
    }

    limit = is_negative ? negative_limit : positive_limit;

    while (c != EOF && !isspace((unsigned char)c)) {
        unsigned int digit;

        if (c < '0' || c > '9') {
            return false;
        }

        if (digit_count >= MAX_NUMERIC_DIGITS) {
            return false;
        }

        ++digit_count;
        have_digit = true;
        digit = (unsigned int)(c - '0');

        if (result > limit / UINTMAX_C(10) ||
            (result == limit / UINTMAX_C(10) &&
             (uintmax_t)digit > limit % UINTMAX_C(10))) {
            return false;
        }

        result = result * UINTMAX_C(10) + (uintmax_t)digit;
        c = input_get(input);
    }

    if (input->error || !have_digit) {
        return false;
    }

    *negative = is_negative;
    *magnitude = result;
    return true;
}

static bool read_size(Input *input, size_t *value)
{
    bool negative;
    uintmax_t magnitude;

    if (value == NULL ||
        !read_magnitude(input, false, (uintmax_t)SIZE_MAX,
                        (uintmax_t)SIZE_MAX, &negative, &magnitude)) {
        return false;
    }

    *value = (size_t)magnitude;
    return true;
}

static bool read_int(Input *input, int *value)
{
    bool negative;
    uintmax_t magnitude;
    const uintmax_t positive_limit = (uintmax_t)INT_MAX;
    const uintmax_t negative_limit =
        (uintmax_t)(-(INT_MIN + 1)) + UINTMAX_C(1);

    if (value == NULL ||
        !read_magnitude(input, true, positive_limit, negative_limit,
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
    Input input;
    Tuple *tuples = NULL;
    size_t tuple_count;
    size_t i;
    size_t j;
    int k;
    bool result;

    input_init(&input, stdin);

    if (!read_size(&input, &tuple_count) || !read_int(&input, &k)) {
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
        if (!read_size(&input, &tuples[i].count)) {
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
            tuples[i].elements =
                malloc(tuples[i].count * sizeof(*tuples[i].elements));

            if (tuples[i].elements == NULL) {
                fputs("Memory allocation failed\n", stderr);
                free_tuples(tuples, tuple_count);
                return EXIT_FAILURE;
            }
        }

        for (j = 0; j < tuples[i].count; ++j) {
            if (!read_int(&input, &tuples[i].elements[j])) {
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