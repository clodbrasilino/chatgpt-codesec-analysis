#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE ((size_t)4096)

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

typedef struct {
    FILE *stream;
    unsigned char *buffer;
    size_t capacity;
    size_t position;
    size_t length;
    int error;
    int end;
} Input;

static int input_init(Input *input, FILE *stream)
{
    if (input == NULL || stream == NULL) {
        return 0;
    }

    input->stream = stream;
    input->buffer = NULL;
    input->capacity = INPUT_BUFFER_SIZE;
    input->position = 0;
    input->length = 0;
    input->error = 0;
    input->end = 0;

    input->buffer = malloc(input->capacity);
    if (input->buffer == NULL) {
        input->capacity = 0;
        return 0;
    }

    return 1;
}

static void input_destroy(Input *input)
{
    if (input == NULL) {
        return;
    }

    free(input->buffer);
    input->buffer = NULL;
    input->stream = NULL;
    input->capacity = 0;
    input->position = 0;
    input->length = 0;
    input->error = 0;
    input->end = 1;
}

static int input_get(Input *input)
{
    if (input == NULL || input->stream == NULL ||
        input->buffer == NULL || input->capacity == 0 ||
        input->error || input->end) {
        return EOF;
    }

    if (input->position >= input->length) {
        input->length = fread(input->buffer, sizeof *input->buffer,
                              input->capacity, input->stream);
        input->position = 0;

        if (input->length == 0) {
            if (ferror(input->stream)) {
                input->error = 1;
            } else {
                input->end = 1;
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

            if (valid) {
                if (result > limit / UINTMAX_C(10) ||
                    (result == limit / UINTMAX_C(10) &&
                     digit > limit % UINTMAX_C(10))) {
                    valid = 0;
                } else {
                    result = result * UINTMAX_C(10) + digit;
                }
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

static uint64_t absolute_difference(int64_t first, int64_t second)
{
    if (first >= second) {
        return (uint64_t)first - (uint64_t)second;
    }

    return (uint64_t)second - (uint64_t)first;
}

int main(void)
{
    Input input;
    size_t count;
    uint64_t minimum = 0;
    int status = EXIT_FAILURE;

    if (!input_init(&input, stdin)) {
        fputs("Input initialization error\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_size(&input, &count) || count == 0) {
        fputs("Invalid tuple count\n", stderr);
        goto cleanup;
    }

    for (size_t index = 0; index < count; ++index) {
        Tuple tuple;
        uint64_t difference;

        if (!read_int64(&input, &tuple.first) ||
            !read_int64(&input, &tuple.second)) {
            fputs("Invalid tuple input\n", stderr);
            goto cleanup;
        }

        difference = absolute_difference(tuple.first, tuple.second);

        if (index == 0 || difference < minimum) {
            minimum = difference;
        }
    }

    if (printf("%" PRIu64 "\n", minimum) < 0) {
        fputs("Output error\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    input_destroy(&input);
    return status;
}