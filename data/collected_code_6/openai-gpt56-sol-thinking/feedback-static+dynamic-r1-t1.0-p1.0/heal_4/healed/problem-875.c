#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

#define INPUT_BUFFER_SIZE 4096

typedef struct {
    FILE *stream;
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t length;
    int ended;
    int error;
} Input;

static int input_get_character(Input *input)
{
    if (input == NULL || input->stream == NULL) {
        return EOF;
    }

    if (input->position >= input->length) {
        if (input->ended) {
            return EOF;
        }

        input->position = 0;
        input->length = fread(input->buffer, 1, sizeof(input->buffer),
                              input->stream);

        if (input->length == 0) {
            if (ferror(input->stream)) {
                input->error = 1;
            }

            input->ended = 1;
            return EOF;
        }

        if (ferror(input->stream)) {
            input->error = 1;
            input->ended = 1;
        } else if (feof(input->stream)) {
            input->ended = 1;
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
    uint64_t unsigned_first = (uint64_t)first;
    uint64_t unsigned_second = (uint64_t)second;

    if (first >= second) {
        return unsigned_first - unsigned_second;
    }

    return unsigned_second - unsigned_first;
}

int main(void)
{
    Input input = {
        .stream = stdin,
        .position = 0,
        .length = 0,
        .ended = 0,
        .error = 0
    };
    size_t count;
    uint64_t minimum = 0;
    int have_minimum = 0;

    if (!read_size_value(&input, &count) || count == 0) {
        return EXIT_FAILURE;
    }

    for (size_t remaining = count; remaining > 0; --remaining) {
        int64_t first;
        int64_t second;
        uint64_t difference;

        if (!read_int64_value(&input, &first) ||
            !read_int64_value(&input, &second)) {
            return EXIT_FAILURE;
        }

        difference = absolute_difference(first, second);

        if (!have_minimum || difference < minimum) {
            minimum = difference;
            have_minimum = 1;
        }
    }

    if (printf("%" PRIu64 "\n", minimum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}