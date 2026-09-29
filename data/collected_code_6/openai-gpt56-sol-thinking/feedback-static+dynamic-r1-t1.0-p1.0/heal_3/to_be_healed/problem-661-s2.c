#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 4096U

typedef struct {
    FILE *stream;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char data[INPUT_BUFFER_SIZE];
    size_t position;
    size_t length;
    bool failed;
} TokenReader;

static bool read_byte(TokenReader *reader, unsigned char *byte)
{
    if (reader == NULL || reader->stream == NULL || byte == NULL) {
        return false;
    }

    if (reader->position == reader->length) {
        reader->length = fread(reader->data, 1, sizeof(reader->data),
                               reader->stream);
        reader->position = 0;

        if (reader->length == 0) {
            if (ferror(reader->stream)) {
                reader->failed = true;
            }

            return false;
        }
    }

    *byte = reader->data[reader->position++];
    return true;
}

static bool read_token(TokenReader *reader, char *buffer, size_t capacity)
{
    size_t length = 0;
    bool too_long = false;
    unsigned char byte;

    if (reader == NULL || buffer == NULL || capacity < 2) {
        return false;
    }

    buffer[0] = '\0';

    do {
        if (!read_byte(reader, &byte)) {
            return false;
        }
    } while (isspace(byte));

    do {
        if (length < capacity - 1) {
            buffer[length++] = (char)byte;
        } else {
            too_long = true;
        }

        if (!read_byte(reader, &byte)) {
            break;
        }
    } while (!isspace(byte));

    buffer[length] = '\0';

    return !reader->failed && !too_long;
}

static bool parse_size(const char *text, size_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-') {
        return false;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > SIZE_MAX) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

static bool parse_int64(const char *text, int64_t *value)
{
    char *end = NULL;
    intmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0') {
        return false;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return false;
    }

    *value = (int64_t)parsed;
    return true;
}

static int checked_add_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return 1;
    }

    if (right > 0 && left > INT64_MAX - right) {
        return 1;
    }

    if (right < 0 && left < INT64_MIN - right) {
        return -1;
    }

    *result = left + right;
    return 0;
}

bool max_sum_no_three_consecutive(const int64_t *values,
                                  size_t count,
                                  int64_t *result)
{
    int64_t ending_with_zero = 0;
    int64_t ending_with_one = 0;
    int64_t ending_with_two = 0;
    bool one_valid = false;
    bool two_valid = false;

    if (result == NULL || (count != 0 && values == NULL)) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t new_zero = ending_with_zero;
        int64_t new_one;
        int64_t new_two = 0;
        bool new_two_valid = false;
        int status;

        if (one_valid && ending_with_one > new_zero) {
            new_zero = ending_with_one;
        }

        if (two_valid && ending_with_two > new_zero) {
            new_zero = ending_with_two;
        }

        status = checked_add_int64(ending_with_zero, values[i], &new_one);
        if (status != 0) {
            return false;
        }

        if (one_valid) {
            status = checked_add_int64(ending_with_one, values[i], &new_two);

            if (status > 0) {
                return false;
            }

            new_two_valid = status == 0;
        }

        ending_with_zero = new_zero;
        ending_with_one = new_one;
        ending_with_two = new_two;
        one_valid = true;
        two_valid = new_two_valid;
    }

    *result = ending_with_zero;

    if (one_valid && ending_with_one > *result) {
        *result = ending_with_one;
    }

    if (two_valid && ending_with_two > *result) {
        *result = ending_with_two;
    }

    return true;
}

int main(void)
{
    TokenReader reader = {
        .stream = stdin,
        .position = 0,
        .length = 0,
        .failed = false
    };
    size_t token_capacity;
    char *token = NULL;
    size_t count;
    int64_t *values = NULL;
    int64_t result;
    int exit_status = EXIT_FAILURE;

    if (sizeof(uintmax_t) > (SIZE_MAX - 3U) / CHAR_BIT) {
        fputs("Token capacity is too large\n", stderr);
        return EXIT_FAILURE;
    }

    token_capacity = sizeof(uintmax_t) * CHAR_BIT + 3U;
    token = malloc(token_capacity);

    if (token == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_token(&reader, token, token_capacity) ||
        !parse_size(token, &count)) {
        fputs("Invalid element count\n", stderr);
        goto cleanup;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Element count is too large\n", stderr);
        goto cleanup;
    }

    if (count != 0) {
        values = malloc(count * sizeof(*values));

        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            goto cleanup;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_token(&reader, token, token_capacity) ||
            !parse_int64(token, &values[i])) {
            fputs("Invalid element\n", stderr);
            goto cleanup;
        }
    }

    if (!max_sum_no_three_consecutive(values, count, &result)) {
        fputs("Unable to compute the result\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        fputs("Output error\n", stderr);
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(values);
    free(token);
    return exit_status;
}