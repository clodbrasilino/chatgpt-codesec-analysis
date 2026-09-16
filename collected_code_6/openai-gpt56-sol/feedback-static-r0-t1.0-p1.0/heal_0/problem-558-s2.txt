#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uintmax_t magnitude(intmax_t value)
{
    return value < 0 ? (uintmax_t)(-(value + 1)) + UINTMAX_C(1)
                     : (uintmax_t)value;
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

int main(void)
{
    intmax_t first;
    intmax_t second;

    if (scanf("%" SCNdMAX " %" SCNdMAX, &first, &second) != 2) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (printf("%" PRIuMAX "\n", digit_distance(first, second)) < 0) {
        return 1;
    }

    return 0;
}