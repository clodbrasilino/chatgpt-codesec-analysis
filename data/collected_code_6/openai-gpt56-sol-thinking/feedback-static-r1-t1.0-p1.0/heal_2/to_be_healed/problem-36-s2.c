#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_CAPACITY 4096U

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    if (a >= modulus - b) {
        return a - (modulus - b);
    }

    return a + b;
}

static uint64_t multiply_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    uint64_t result = 0;

    while (b != 0) {
        if ((b & UINT64_C(1)) != 0) {
            result = add_mod(result, a, modulus);
        }

        b >>= 1;

        if (b != 0) {
            a = add_mod(a, a, modulus);
        }
    }

    return result;
}

static uint64_t power_mod(uint64_t base, uint64_t exponent, uint64_t modulus)
{
    uint64_t result = UINT64_C(1) % modulus;

    base %= modulus;

    while (exponent != 0) {
        if ((exponent & UINT64_C(1)) != 0) {
            result = multiply_mod(result, base, modulus);
        }

        exponent >>= 1;

        if (exponent != 0) {
            base = multiply_mod(base, base, modulus);
        }
    }

    return result;
}

bool find_nth_digit(uint64_t numerator, uint64_t denominator,
                    uint64_t position, unsigned int *digit)
{
    uint64_t remainder;
    uint64_t accumulated = 0;
    unsigned int quotient = 0;
    unsigned int i;

    if (digit == NULL || denominator == 0 || numerator >= denominator ||
        position == 0) {
        return false;
    }

    remainder = multiply_mod(
        numerator,
        power_mod(UINT64_C(10), position - UINT64_C(1), denominator),
        denominator
    );

    for (i = 0; i < 10U; ++i) {
        if (accumulated >= denominator - remainder) {
            accumulated -= denominator - remainder;
            ++quotient;
        } else {
            accumulated += remainder;
        }
    }

    *digit = quotient;
    return true;
}

static bool read_input(unsigned char *buffer, size_t capacity, size_t *length)
{
    size_t count;

    if (buffer == NULL || length == NULL || capacity == 0) {
        return false;
    }

    count = fread(buffer, 1, capacity, stdin);

    if (ferror(stdin) || count == capacity || !feof(stdin)) {
        return false;
    }

    *length = count;
    return true;
}

static bool parse_uint64(const unsigned char *buffer, size_t length,
                         size_t *offset, uint64_t *value)
{
    uint64_t result = 0;
    size_t index;

    if (buffer == NULL || offset == NULL || value == NULL ||
        *offset > length) {
        return false;
    }

    index = *offset;

    while (index < length && isspace(buffer[index])) {
        ++index;
    }

    if (index == length || buffer[index] < '0' || buffer[index] > '9') {
        return false;
    }

    while (index < length &&
           buffer[index] >= '0' && buffer[index] <= '9') {
        unsigned int current_digit =
            (unsigned int)(buffer[index] - (unsigned char)'0');

        if (result > (UINT64_MAX - current_digit) / UINT64_C(10)) {
            return false;
        }

        result = result * UINT64_C(10) + current_digit;
        ++index;
    }

    if (index < length && !isspace(buffer[index])) {
        return false;
    }

    *offset = index;
    *value = result;
    return true;
}

static bool only_whitespace_remaining(const unsigned char *buffer,
                                      size_t length, size_t offset)
{
    if (buffer == NULL || offset > length) {
        return false;
    }

    while (offset < length) {
        if (!isspace(buffer[offset])) {
            return false;
        }

        ++offset;
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char input[INPUT_CAPACITY];
    size_t input_length;
    size_t offset = 0;
    uint64_t numerator;
    uint64_t denominator;
    uint64_t position;
    unsigned int digit;

    if (!read_input(input, sizeof(input), &input_length) ||
        !parse_uint64(input, input_length, &offset, &numerator) ||
        !parse_uint64(input, input_length, &offset, &denominator) ||
        !parse_uint64(input, input_length, &offset, &position) ||
        !only_whitespace_remaining(input, input_length, offset)) {
        return EXIT_FAILURE;
    }

    if (!find_nth_digit(numerator, denominator, position, &digit)) {
        return EXIT_FAILURE;
    }

    if (printf("%u\n", digit) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}