#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <ctype.h>

#define INPUT_BUFFER_SIZE 4096U

typedef struct {
    FILE *stream;
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t length;
    bool end;
    bool error;
} InputReader;

static bool input_reader_init(InputReader *reader, FILE *stream)
{
    if (reader == NULL || stream == NULL) {
        return false;
    }

    reader->stream = stream;
    reader->position = 0;
    reader->length = 0;
    reader->end = false;
    reader->error = false;

    return true;
}

static int input_reader_get(InputReader *reader)
{
    size_t bytes_read;

    if (reader == NULL ||
        reader->stream == NULL ||
        reader->end ||
        reader->error) {
        return EOF;
    }

    if (reader->position == reader->length) {
        bytes_read = fread(
            reader->buffer,
            sizeof(reader->buffer[0]),
            sizeof(reader->buffer),
            reader->stream
        );

        if (bytes_read == 0) {
            if (ferror(reader->stream)) {
                reader->error = true;
            } else if (feof(reader->stream)) {
                reader->end = true;
            } else {
                reader->error = true;
            }

            return EOF;
        }

        reader->position = 0;
        reader->length = bytes_read;
    }

    return (int)reader->buffer[reader->position++];
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

int main(void)
{
    InputReader reader;
    size_t tuple_count;
    size_t tuple_size;
    size_t i;
    size_t j;
    int k;
    int element;
    bool all_have_k = true;

    if (!input_reader_init(&reader, stdin)) {
        fputs("Input initialization failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_size(&reader, &tuple_count) ||
        !read_int(&reader, &k)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < tuple_count; ++i) {
        bool found = false;

        if (!read_size(&reader, &tuple_size)) {
            fputs("Invalid tuple size\n", stderr);
            return EXIT_FAILURE;
        }

        for (j = 0; j < tuple_size; ++j) {
            if (!read_int(&reader, &element)) {
                fputs("Invalid tuple element\n", stderr);
                return EXIT_FAILURE;
            }

            if (element == k) {
                found = true;
            }
        }

        if (!found) {
            all_have_k = false;
        }
    }

    if (puts(all_have_k ? "true" : "false") == EOF ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}