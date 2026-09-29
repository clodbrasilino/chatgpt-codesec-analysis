#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    INPUT_BUFFER_SIZE = 4096
};

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t length;
    bool error;
    bool end_of_file;
} InputScanner;

static int scanner_get(InputScanner *scanner)
{
    if (scanner == NULL || scanner->error || scanner->end_of_file) {
        return EOF;
    }

    if (scanner->position == scanner->length) {
        scanner->position = 0;
        scanner->length = fread(
            scanner->buffer,
            sizeof scanner->buffer[0],
            sizeof scanner->buffer,
            stdin
        );

        if (ferror(stdin)) {
            scanner->error = true;
            return EOF;
        }

        if (scanner->length == 0) {
            scanner->end_of_file = true;
            return EOF;
        }
    }

    return (int)scanner->buffer[scanner->position++];
}

static bool read_non_whitespace(InputScanner *scanner, int *value)
{
    if (scanner == NULL || value == NULL) {
        return false;
    }

    int ch;

    do {
        ch = scanner_get(scanner);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return false;
    }

    *value = ch;
    return true;
}

static bool read_size(InputScanner *scanner, size_t *value)
{
    if (scanner == NULL || value == NULL) {
        return false;
    }

    int ch;

    if (!read_non_whitespace(scanner, &ch)) {
        return false;
    }

    bool valid = true;
    bool have_digit = false;
    size_t parsed = 0;

    if (ch == '+' || ch == '-') {
        valid = ch != '-';
        ch = scanner_get(scanner);
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (ch >= '0' && ch <= '9') {
            const size_t digit = (size_t)(ch - '0');
            have_digit = true;

            if (parsed > (SIZE_MAX - digit) / (size_t)10) {
                valid = false;
            } else {
                parsed = parsed * (size_t)10 + digit;
            }
        } else {
            valid = false;
        }

        ch = scanner_get(scanner);
    }

    if (scanner->error || !valid || !have_digit) {
        return false;
    }

    *value = parsed;
    return true;
}

static bool read_int32(InputScanner *scanner, int32_t *value)
{
    if (scanner == NULL || value == NULL) {
        return false;
    }

    int ch;

    if (!read_non_whitespace(scanner, &ch)) {
        return false;
    }

    bool negative = false;
    bool valid = true;
    bool have_digit = false;

    if (ch == '+' || ch == '-') {
        negative = ch == '-';
        ch = scanner_get(scanner);
    }

    const uintmax_t limit = negative
        ? (uintmax_t)INT32_MAX + UINTMAX_C(1)
        : (uintmax_t)INT32_MAX;

    uintmax_t magnitude = 0;

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (ch >= '0' && ch <= '9') {
            const uintmax_t digit = (uintmax_t)(ch - '0');
            have_digit = true;

            if (magnitude > (limit - digit) / UINTMAX_C(10)) {
                valid = false;
            } else {
                magnitude = magnitude * UINTMAX_C(10) + digit;
            }
        } else {
            valid = false;
        }

        ch = scanner_get(scanner);
    }

    if (scanner->error || !valid || !have_digit) {
        return false;
    }

    if (negative) {
        if (magnitude == (uintmax_t)INT32_MAX + UINTMAX_C(1)) {
            *value = INT32_MIN;
        } else {
            *value = -(int32_t)magnitude;
        }
    } else {
        *value = (int32_t)magnitude;
    }

    return true;
}

int main(void)
{
    InputScanner scanner = { 0 };
    size_t count;

    if (!read_size(&scanner, &count) || count == 0) {
        return EXIT_FAILURE;
    }

    int32_t first;
    int32_t second;

    if (!read_int32(&scanner, &first) ||
        !read_int32(&scanner, &second)) {
        return EXIT_FAILURE;
    }

    int64_t maximum = (int64_t)first * (int64_t)second;

    for (size_t i = 1; i < count; ++i) {
        if (!read_int32(&scanner, &first) ||
            !read_int32(&scanner, &second)) {
            return EXIT_FAILURE;
        }

        const int64_t product = (int64_t)first * (int64_t)second;

        if (product > maximum) {
            maximum = product;
        }
    }

    if (printf("%" PRId64 "\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}