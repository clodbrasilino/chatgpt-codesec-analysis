#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool read_decimal_token(
    FILE *stream,
    bool allow_negative,
    uintmax_t positive_limit,
    uintmax_t negative_limit,
    bool *is_negative,
    uintmax_t *magnitude)
{
    if (stream == NULL || is_negative == NULL || magnitude == NULL) {
        return false;
    }

    int character;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);

        if (character == EOF) {
            return false;
        }
    } while (isspace((unsigned char)character) != 0);

    bool negative = false;
    bool valid = true;
    bool has_digit = false;
    uintmax_t value = 0;

    if (character == '+' || character == '-') {
        negative = character == '-';

        if (negative && !allow_negative) {
            valid = false;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);
    }

    const uintmax_t limit =
        negative && allow_negative ? negative_limit : positive_limit;

    while (character != EOF &&
           isspace((unsigned char)character) == 0) {
        if (character >= '0' && character <= '9') {
            const uintmax_t digit =
                (uintmax_t)((unsigned char)character - (unsigned char)'0');

            has_digit = true;

            if (value > limit / UINTMAX_C(10) ||
                (value == limit / UINTMAX_C(10) &&
                 digit > limit % UINTMAX_C(10))) {
                valid = false;
            } else {
                value = value * UINTMAX_C(10) + digit;
            }
        } else {
            valid = false;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);
    }

    if (character == EOF && ferror(stream)) {
        return false;
    }

    if (!valid || !has_digit) {
        return false;
    }

    *is_negative = negative;
    *magnitude = value;
    return true;
}

static bool read_size(FILE *stream, size_t *value)
{
    if (stream == NULL || value == NULL) {
        return false;
    }

    bool negative;
    uintmax_t magnitude;

    if (!read_decimal_token(
            stream,
            false,
            (uintmax_t)SIZE_MAX,
            (uintmax_t)SIZE_MAX,
            &negative,
            &magnitude)) {
        return false;
    }

    *value = (size_t)magnitude;
    return true;
}

static bool read_int64(FILE *stream, int64_t *value)
{
    if (stream == NULL || value == NULL) {
        return false;
    }

    bool negative;
    uintmax_t magnitude;
    const uintmax_t negative_limit =
        (uintmax_t)INT64_MAX + UINTMAX_C(1);

    if (!read_decimal_token(
            stream,
            true,
            (uintmax_t)INT64_MAX,
            negative_limit,
            &negative,
            &magnitude)) {
        return false;
    }

    if (!negative) {
        *value = (int64_t)magnitude;
    } else if (magnitude == negative_limit) {
        *value = INT64_MIN;
    } else {
        *value = -(int64_t)magnitude;
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
    size_t count;

    if (!read_size(stdin, &count) || count == 0) {
        return EXIT_FAILURE;
    }

    uint64_t minimum_difference = UINT64_MAX;

    for (size_t i = 0; i < count; ++i) {
        int64_t first;
        int64_t second;

        if (!read_int64(stdin, &first) ||
            !read_int64(stdin, &second)) {
            return EXIT_FAILURE;
        }

        const uint64_t difference =
            absolute_difference(first, second);

        if (difference < minimum_difference) {
            minimum_difference = difference;
        }
    }

    if (printf("%" PRIu64 "\n", minimum_difference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}