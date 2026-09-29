#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t magnitude(intmax_t value)
{
    if (value < 0) {
        return (uintmax_t)(-(value + INTMAX_C(1))) + UINTMAX_C(1);
    }

    return (uintmax_t)value;
}

static uintmax_t digit_distance(intmax_t first, intmax_t second)
{
    uintmax_t left = magnitude(first);
    uintmax_t right = magnitude(second);
    uintmax_t distance = 0;

    do {
        uintmax_t left_digit = left % UINTMAX_C(10);
        uintmax_t right_digit = right % UINTMAX_C(10);

        distance += left_digit > right_digit
            ? left_digit - right_digit
            : right_digit - left_digit;

        left /= UINTMAX_C(10);
        right /= UINTMAX_C(10);
    } while (left != 0 || right != 0);

    return distance;
}

static int read_integer(intmax_t *value)
{
    int result;

    if (value == NULL) {
        return 0;
    }

    result = scanf("%" SCNdMAX, value);
    return result == 1;
}

int main(void)
{
    intmax_t first;
    intmax_t second;
    int character;

    if (!read_integer(&first) || !read_integer(&second)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    do {
        character = getchar();
    } while (character == ' ' || character == '\t' ||
             character == '\n' || character == '\r' ||
             character == '\f' || character == '\v');

    if (character != EOF) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIuMAX "\n", digit_distance(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}