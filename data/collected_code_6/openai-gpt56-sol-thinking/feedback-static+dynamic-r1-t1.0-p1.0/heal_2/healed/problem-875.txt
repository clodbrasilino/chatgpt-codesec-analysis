#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

#define INPUT_BUFFER_SIZE 4096

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

typedef struct {
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t length;
    int error;
} Input;

static int input_get_character(Input *input)
{
    if (input == NULL) {
        return EOF;
    }

    if (input->position >= input->length) {
        input->length = fread(input->buffer, 1, sizeof(input->buffer), stdin);
        input->position = 0;

        if (input->length == 0) {
            if (ferror(stdin)) {
                input->error = 1;
            }
            return EOF;
        }
    }

    return (int)input->buffer[input->position++];
}

static int input_is_whitespace(int character)
{
    return character == ' ' || character == '\t' ||
           character == '\n' || character == '\r' ||
           character == '\f' || character == '\v';
}

static int read_size_value(Input *input, size_t *value)
{
    int character;
    size_t result = 0;

    if (input == NULL || value == NULL) {
        return 0;
    }

    do {
        character = input_get_character(input);
        if (character == EOF) {
            return 0;
        }
    } while (input_is_whitespace(character));

    if (character == '+') {
        character = input_get_character(input);
    }

    if (character < '0' || character > '9') {
        return 0;
    }

    do {
        size_t digit = (size_t)(character - '0');

        if (result > (SIZE_MAX - digit) / (size_t)10) {
            return 0;
        }

        result = result * (size_t)10 + digit;
        character = input_get_character(input);
    } while (character >= '0' && character <= '9');

    if (character == EOF) {
        if (input->error) {
            return 0;
        }
    } else if (!input_is_whitespace(character)) {
        return 0;
    }

    *value = result;
    return 1;
}

static int read_int64_value(Input *input, int64_t *value)
{
    int character;
    int negative = 0;
    uint64_t result = 0;
    uint64_t limit;

    if (input == NULL || value == NULL) {
        return 0;
    }

    do {
        character = input_get_character(input);
        if (character == EOF) {
            return 0;
        }
    } while (input_is_whitespace(character));

    if (character == '-' || character == '+') {
        negative = character == '-';
        character = input_get_character(input);
    }

    if (character < '0' || character > '9') {
        return 0;
    }

    limit = negative
                ? (uint64_t)INT64_MAX + UINT64_C(1)
                : (uint64_t)INT64_MAX;

    do {
        uint64_t digit = (uint64_t)(character - '0');

        if (result > (limit - digit) / UINT64_C(10)) {
            return 0;
        }

        result = result * UINT64_C(10) + digit;
        character = input_get_character(input);
    } while (character >= '0' && character <= '9');

    if (character == EOF) {
        if (input->error) {
            return 0;
        }
    } else if (!input_is_whitespace(character)) {
        return 0;
    }

    if (negative) {
        if (result == (uint64_t)INT64_MAX + UINT64_C(1)) {
            *value = INT64_MIN;
        } else {
            *value = -(int64_t)result;
        }
    } else {
        *value = (int64_t)result;
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

static int find_minimum_tuple_difference(const Tuple *tuples,
                                         size_t count,
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
    Input input = {0};
    size_t count;
    Tuple *tuples;
    uint64_t minimum;

    if (!read_size_value(&input, &count) ||
        count == 0 ||
        count > SIZE_MAX / sizeof(Tuple)) {
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int64_value(&input, &tuples[i].first) ||
            !read_int64_value(&input, &tuples[i].second)) {
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (!find_minimum_tuple_difference(tuples, count, &minimum)) {
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);

    if (printf("%" PRIu64 "\n", minimum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}