#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

typedef struct {
    unsigned char buffer[4096];
    size_t position;
    size_t length;
    bool error;
} Input;

static int input_get(Input *input)
{
    if (input == NULL || input->error) {
        return EOF;
    }

    if (input->position == input->length) {
        input->length = fread(
            input->buffer,
            sizeof(input->buffer[0]),
            sizeof(input->buffer),
            stdin);
        input->position = 0;

        if (input->length == 0) {
            if (ferror(stdin)) {
                input->error = true;
            }

            return EOF;
        }
    }

    return (int)input->buffer[input->position++];
}

static bool read_nonspace(Input *input, int *character)
{
    if (input == NULL || character == NULL) {
        return false;
    }

    int current;

    do {
        current = input_get(input);
    } while (current != EOF && isspace((unsigned char)current));

    if (current == EOF) {
        return false;
    }

    *character = current;
    return true;
}

static bool read_size(Input *input, size_t *value)
{
    if (input == NULL || value == NULL) {
        return false;
    }

    int character;

    if (!read_nonspace(input, &character) || character == '-') {
        return false;
    }

    if (character == '+') {
        character = input_get(input);
    }

    size_t result = 0;
    bool has_digit = false;

    while (character != EOF && !isspace((unsigned char)character)) {
        if (character < '0' || character > '9') {
            return false;
        }

        size_t digit = (size_t)(character - '0');

        if (result > (SIZE_MAX - digit) / 10U) {
            return false;
        }

        result = result * 10U + digit;
        has_digit = true;
        character = input_get(input);
    }

    if (input->error || !has_digit) {
        return false;
    }

    *value = result;
    return true;
}

static bool read_int64(Input *input, int64_t *value)
{
    if (input == NULL || value == NULL) {
        return false;
    }

    int character;

    if (!read_nonspace(input, &character)) {
        return false;
    }

    bool negative = false;

    if (character == '-' || character == '+') {
        negative = character == '-';
        character = input_get(input);
    }

    const uint64_t limit = negative
        ? (uint64_t)INT64_MAX + UINT64_C(1)
        : (uint64_t)INT64_MAX;

    uint64_t magnitude = 0;
    bool has_digit = false;

    while (character != EOF && !isspace((unsigned char)character)) {
        if (character < '0' || character > '9') {
            return false;
        }

        uint64_t digit = (uint64_t)(character - '0');

        if (magnitude > (limit - digit) / UINT64_C(10)) {
            return false;
        }

        magnitude = magnitude * UINT64_C(10) + digit;
        has_digit = true;
        character = input_get(input);
    }

    if (input->error || !has_digit) {
        return false;
    }

    if (negative) {
        if (magnitude == (uint64_t)INT64_MAX + UINT64_C(1)) {
            *value = INT64_MIN;
        } else {
            *value = -(int64_t)magnitude;
        }
    } else {
        *value = (int64_t)magnitude;
    }

    return true;
}

static uint64_t absolute_difference(int64_t first, int64_t second)
{
    if (first >= second) {
        return (uint64_t)first - (uint64_t)second;
    }

    return (uint64_t)second - (uint64_t)first;
}

static bool find_minimum_tuple_difference(
    const Tuple *tuples,
    size_t count,
    uint64_t *minimum_difference)
{
    if (tuples == NULL || count == 0 || minimum_difference == NULL) {
        return false;
    }

    uint64_t minimum = UINT64_MAX;

    for (size_t i = 0; i < count; ++i) {
        uint64_t difference =
            absolute_difference(tuples[i].first, tuples[i].second);

        if (difference < minimum) {
            minimum = difference;
        }
    }

    *minimum_difference = minimum;
    return true;
}

int main(void)
{
    Input input = {
        .position = 0,
        .length = 0,
        .error = false
    };

    size_t count;

    if (!read_size(&input, &count) ||
        count == 0 ||
        count > SIZE_MAX / sizeof(Tuple)) {
        return EXIT_FAILURE;
    }

    Tuple *tuples = malloc(count * sizeof(*tuples));

    if (tuples == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int64(&input, &tuples[i].first) ||
            !read_int64(&input, &tuples[i].second)) {
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    uint64_t minimum_difference;

    if (!find_minimum_tuple_difference(
            tuples,
            count,
            &minimum_difference)) {
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);

    if (printf("%" PRIu64 "\n", minimum_difference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}