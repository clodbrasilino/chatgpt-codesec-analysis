#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE ((size_t)4096)

typedef struct {
    FILE *stream;
    unsigned char *buffer;
    size_t capacity;
    size_t position;
    size_t length;
    bool error;
} Input;

static bool input_init(Input *input, FILE *stream)
{
    if (input == NULL || stream == NULL) {
        return false;
    }

    input->stream = stream;
    input->buffer = NULL;
    input->capacity = INPUT_BUFFER_SIZE;
    input->position = 0;
    input->length = 0;
    input->error = false;

    input->buffer = malloc(input->capacity);
    if (input->buffer == NULL) {
        input->stream = NULL;
        input->capacity = 0;
        return false;
    }

    return true;
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
    input->error = false;
}

static int input_get(Input *input)
{
    if (input == NULL ||
        input->stream == NULL ||
        input->buffer == NULL ||
        input->capacity == 0 ||
        input->error) {
        return EOF;
    }

    if (input->position >= input->length) {
        input->length = fread(
            input->buffer,
            sizeof(*input->buffer),
            input->capacity,
            input->stream
        );
        input->position = 0;

        if (input->length == 0) {
            if (ferror(input->stream)) {
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

        if (result > (SIZE_MAX - digit) / (size_t)10) {
            return false;
        }

        result = result * (size_t)10 + digit;
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
        *value = magnitude == (uint64_t)INT64_MAX + UINT64_C(1)
            ? INT64_MIN
            : -(int64_t)magnitude;
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

int main(void)
{
    Input input;

    if (!input_init(&input, stdin)) {
        return EXIT_FAILURE;
    }

    int status = EXIT_FAILURE;
    size_t count;

    if (!read_size(&input, &count) || count == 0) {
        goto cleanup;
    }

    uint64_t minimum_difference = UINT64_MAX;

    for (size_t i = 0; i < count; ++i) {
        int64_t first;
        int64_t second;

        if (!read_int64(&input, &first) ||
            !read_int64(&input, &second)) {
            goto cleanup;
        }

        uint64_t difference = absolute_difference(first, second);

        if (difference < minimum_difference) {
            minimum_difference = difference;
        }
    }

    if (printf("%" PRIu64 "\n", minimum_difference) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    input_destroy(&input);
    return status;
}