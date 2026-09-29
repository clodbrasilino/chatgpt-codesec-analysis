#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

typedef struct {
    FILE *stream;
    unsigned char buffer[4096];
    size_t position;
    size_t length;
    int error;
} Input;

static void input_init(Input *input, FILE *stream)
{
    input->stream = stream;
    input->position = 0;
    input->length = 0;
    input->error = 0;
}

static int input_get(Input *input)
{
    if (input == NULL || input->stream == NULL) {
        return EOF;
    }

    if (input->position >= input->length) {
        input->length = fread(input->buffer, 1, sizeof(input->buffer),
                              input->stream);
        input->position = 0;

        if (input->length == 0) {
            if (ferror(input->stream)) {
                input->error = 1;
            }
            return EOF;
        }
    }

    return (int)input->buffer[input->position++];
}

static int read_magnitude(Input *input, int allow_negative,
                          uintmax_t positive_limit,
                          uintmax_t negative_limit,
                          int *negative, uintmax_t *magnitude)
{
    int ch;
    int sign = 0;
    int saw_digit = 0;
    int valid = 1;
    uintmax_t result = 0;
    uintmax_t limit;

    if (input == NULL || input->stream == NULL ||
        negative == NULL || magnitude == NULL) {
        return 0;
    }

    do {
        ch = input_get(input);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    if (ch == '+' || ch == '-') {
        sign = ch == '-';

        if (sign && !allow_negative) {
            valid = 0;
        }

        ch = input_get(input);
    }

    limit = sign ? negative_limit : positive_limit;

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (ch >= '0' && ch <= '9') {
            uintmax_t digit = (uintmax_t)(ch - '0');

            saw_digit = 1;

            if (result > limit / 10 ||
                (result == limit / 10 && digit > limit % 10)) {
                valid = 0;
            } else {
                result = result * 10 + digit;
            }
        } else {
            valid = 0;
        }

        ch = input_get(input);
    }

    if (input->error) {
        valid = 0;
    }

    if (!valid || !saw_digit) {
        return 0;
    }

    *negative = sign;
    *magnitude = result;
    return 1;
}

static int read_size(Input *input, size_t *value)
{
    int negative;
    uintmax_t magnitude;

    if (value == NULL ||
        !read_magnitude(input, 0, (uintmax_t)SIZE_MAX,
                        (uintmax_t)SIZE_MAX, &negative, &magnitude)) {
        return 0;
    }

    *value = (size_t)magnitude;
    return 1;
}

static int read_int64(Input *input, int64_t *value)
{
    int negative;
    uintmax_t magnitude;
    const uintmax_t positive_limit = (uintmax_t)INT64_MAX;
    const uintmax_t negative_limit = (uintmax_t)INT64_MAX + UINTMAX_C(1);

    if (value == NULL ||
        !read_magnitude(input, 1, positive_limit, negative_limit,
                        &negative, &magnitude)) {
        return 0;
    }

    if (negative) {
        if (magnitude == negative_limit) {
            *value = INT64_MIN;
        } else {
            *value = -(int64_t)magnitude;
        }
    } else {
        *value = (int64_t)magnitude;
    }

    return 1;
}

static uint64_t absolute_difference(int64_t a, int64_t b)
{
    if (a >= b) {
        return (uint64_t)a - (uint64_t)b;
    }

    return (uint64_t)b - (uint64_t)a;
}

static int find_minimum_pair_difference(const Tuple *tuples, size_t count,
                                        uint64_t *minimum)
{
    uint64_t result;

    if (tuples == NULL || minimum == NULL || count == 0) {
        return 0;
    }

    result = absolute_difference(tuples[0].first, tuples[0].second);

    for (size_t i = 1; i < count; ++i) {
        uint64_t difference =
            absolute_difference(tuples[i].first, tuples[i].second);

        if (difference < result) {
            result = difference;
        }
    }

    *minimum = result;
    return 1;
}

int main(void)
{
    Input input;
    size_t count;
    Tuple *tuples;
    uint64_t minimum;

    input_init(&input, stdin);

    if (!read_size(&input, &count) || count == 0) {
        fputs("Invalid tuple count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Tuple count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int64(&input, &tuples[i].first) ||
            !read_int64(&input, &tuples[i].second)) {
            fputs("Invalid tuple input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (!find_minimum_pair_difference(tuples, count, &minimum)) {
        fputs("Unable to calculate minimum difference\n", stderr);
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);

    if (printf("%" PRIu64 "\n", minimum) < 0) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}