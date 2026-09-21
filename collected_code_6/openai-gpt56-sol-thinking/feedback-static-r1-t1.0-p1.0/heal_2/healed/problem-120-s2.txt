#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool read_non_whitespace(int *value)
{
    if (value == NULL) {
        return false;
    }

    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return false;
    }

    *value = ch;
    return true;
}

static bool read_size(size_t *value)
{
    if (value == NULL) {
        return false;
    }

    int ch;

    if (!read_non_whitespace(&ch)) {
        return false;
    }

    bool valid = true;
    bool have_digit = false;
    size_t parsed = 0;

    if (ch == '+' || ch == '-') {
        if (ch == '-') {
            valid = false;
        }
        ch = fgetc(stdin);
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (ch >= '0' && ch <= '9') {
            size_t digit = (size_t)(ch - '0');
            have_digit = true;

            if (parsed > (SIZE_MAX - digit) / 10) {
                valid = false;
            } else {
                parsed = parsed * 10 + digit;
            }
        } else {
            valid = false;
        }

        ch = fgetc(stdin);
    }

    if (ferror(stdin) || !valid || !have_digit) {
        return false;
    }

    *value = parsed;
    return true;
}

static bool read_int32(int32_t *value)
{
    if (value == NULL) {
        return false;
    }

    int ch;

    if (!read_non_whitespace(&ch)) {
        return false;
    }

    bool negative = false;
    bool valid = true;
    bool have_digit = false;

    if (ch == '+' || ch == '-') {
        negative = ch == '-';
        ch = fgetc(stdin);
    }

    uintmax_t limit = negative
        ? (uintmax_t)INT32_MAX + 1u
        : (uintmax_t)INT32_MAX;
    uintmax_t magnitude = 0;

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (ch >= '0' && ch <= '9') {
            uintmax_t digit = (uintmax_t)(ch - '0');
            have_digit = true;

            if (magnitude > (limit - digit) / 10u) {
                valid = false;
            } else {
                magnitude = magnitude * 10u + digit;
            }
        } else {
            valid = false;
        }

        ch = fgetc(stdin);
    }

    if (ferror(stdin) || !valid || !have_digit) {
        return false;
    }

    if (negative) {
        if (magnitude == (uintmax_t)INT32_MAX + 1u) {
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
    size_t count;

    if (!read_size(&count) || count == 0) {
        return EXIT_FAILURE;
    }

    int32_t first;
    int32_t second;

    if (!read_int32(&first) || !read_int32(&second)) {
        return EXIT_FAILURE;
    }

    int64_t maximum = (int64_t)first * (int64_t)second;

    for (size_t i = 1; i < count; ++i) {
        if (!read_int32(&first) || !read_int32(&second)) {
            return EXIT_FAILURE;
        }

        int64_t product = (int64_t)first * (int64_t)second;

        if (product > maximum) {
            maximum = product;
        }
    }

    if (printf("%" PRId64 "\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}