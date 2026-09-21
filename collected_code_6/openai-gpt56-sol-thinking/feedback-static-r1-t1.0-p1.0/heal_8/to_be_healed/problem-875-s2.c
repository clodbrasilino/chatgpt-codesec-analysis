#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    FILE *stream;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];
    size_t position;
    size_t length;
    bool error;
} Input;

static void input_init(Input *input, FILE *stream)
{
    input->stream = stream;
    input->position = 0;
    input->length = 0;
    input->error = false;
}

static int input_get(Input *input)
{
    if (input == NULL || input->stream == NULL || input->error) {
        return EOF;
    }

    if (input->position == input->length) {
        input->length = fread(
            input->buffer,
            sizeof input->buffer[0],
            sizeof input->buffer,
            input->stream);
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

static bool read_decimal_token(
    Input *input,
    bool allow_negative,
    uintmax_t positive_limit,
    uintmax_t negative_limit,
    bool *is_negative,
    uintmax_t *magnitude)
{
    if (input == NULL || is_negative == NULL || magnitude == NULL) {
        return false;
    }

    int character;

    do {
        character = input_get(input);

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

        character = input_get(input);
    }

    const uintmax_t limit =
        negative && allow_negative ? negative_limit : positive_limit;
    const uintmax_t quotient = limit / UINTMAX_C(10);
    const uintmax_t remainder = limit % UINTMAX_C(10);

    while (character != EOF &&
           isspace((unsigned char)character) == 0) {
        if (character >= '0' && character <= '9') {
            const uintmax_t digit =
                (uintmax_t)(character - '0');

            has_digit = true;

            if (value > quotient ||
                (value == quotient && digit > remainder)) {
                valid = false;
            } else {
                value = value * UINTMAX_C(10) + digit;
            }
        } else {
            valid = false;
        }

        character = input_get(input);
    }

    if (input->error || !valid || !has_digit) {
        return false;
    }

    *is_negative = negative;
    *magnitude = value;
    return true;
}

static bool read_size(Input *input, size_t *value)
{
    if (input == NULL || value == NULL) {
        return false;
    }

    bool negative;
    uintmax_t magnitude;

    if (!read_decimal_token(
            input,
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

static bool read_int64(Input *input, int64_t *value)
{
    if (input == NULL || value == NULL) {
        return false;
    }

    bool negative;
    uintmax_t magnitude;
    const uintmax_t negative_limit =
        (uintmax_t)INT64_MAX + UINTMAX_C(1);

    if (!read_decimal_token(
            input,
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
    Input input;
    input_init(&input, stdin);

    size_t count;

    if (!read_size(&input, &count) || count == 0) {
        return EXIT_FAILURE;
    }

    uint64_t minimum_difference = UINT64_MAX;

    for (size_t i = 0; i < count; ++i) {
        int64_t first;
        int64_t second;

        if (!read_int64(&input, &first) ||
            !read_int64(&input, &second)) {
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