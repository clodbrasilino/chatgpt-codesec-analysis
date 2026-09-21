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
    int error;
} Input;

static void input_init(Input *input, FILE *stream)
{
    if (input != NULL) {
        input->stream = stream;
        input->error = 0;
    }
}

static int input_get(Input *input)
{
    int ch;

    if (input == NULL || input->stream == NULL) {
        return EOF;
    }

    ch = fgetc(input->stream);
    if (ch == EOF && ferror(input->stream)) {
        input->error = 1;
    }

    return ch;
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

            if (result > limit / UINTMAX_C(10) ||
                (result == limit / UINTMAX_C(10) &&
                 digit > limit % UINTMAX_C(10))) {
                valid = 0;
            } else {
                result = result * UINTMAX_C(10) + digit;
            }
        } else {
            valid = 0;
        }

        ch = input_get(input);
    }

    if (input->error || !valid || !saw_digit) {
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
    const uintmax_t negative_limit =
        (uintmax_t)INT64_MAX + UINTMAX_C(1);

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

int main(void)
{
    Input input;
    size_t count;
    uint64_t minimum = 0;

    input_init(&input, stdin);

    if (!read_size(&input, &count) || count == 0) {
        fputs("Invalid tuple count\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        Tuple tuple;
        uint64_t difference;

        if (!read_int64(&input, &tuple.first) ||
            !read_int64(&input, &tuple.second)) {
            fputs("Invalid tuple input\n", stderr);
            return EXIT_FAILURE;
        }

        difference = absolute_difference(tuple.first, tuple.second);

        if (i == 0 || difference < minimum) {
            minimum = difference;
        }
    }

    if (printf("%" PRIu64 "\n", minimum) < 0) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}