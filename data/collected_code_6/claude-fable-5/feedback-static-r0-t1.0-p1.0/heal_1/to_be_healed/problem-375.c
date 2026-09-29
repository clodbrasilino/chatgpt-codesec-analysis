#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int round_to_nearest_multiple(long long number, long long multiple, long long *result)
{
    long long quotient;
    long long remainder;
    long long half;

    if (result == NULL) {
        return -1;
    }

    if (multiple == 0) {
        return -1;
    }

    if (multiple < 0) {
        if (multiple == LLONG_MIN) {
            return -1;
        }
        multiple = -multiple;
    }

    quotient = number / multiple;
    remainder = number % multiple;

    if (remainder == 0) {
        *result = number;
        return 0;
    }

    half = multiple / 2;

    if (remainder > 0) {
        if (remainder > half || (remainder == half && (multiple % 2) == 0)) {
            if (quotient > (LLONG_MAX / multiple) - 1) {
                return -1;
            }
            *result = (quotient + 1) * multiple;
        } else {
            *result = quotient * multiple;
        }
    } else {
        if (-remainder > half || (-remainder == half && (multiple % 2) == 0)) {
            if (quotient < (LLONG_MIN / multiple) + 1) {
                return -1;
            }
            *result = (quotient - 1) * multiple;
        } else {
            *result = quotient * multiple;
        }
    }

    return 0;
}

int main(void)
{
    long long test_numbers[] = {17, -17, 25, 12, 0, 100, -98};
    /* Possible weaknesses found:
     *  Variable 'test_multiples' can be declared as const array [constVariable]
     */
    long long test_multiples[] = {5, 5, 10, 4, 7, 3, 10};
    size_t count = sizeof(test_numbers) / sizeof(test_numbers[0]);
    size_t i;
    long long rounded;

    for (i = 0; i < count; i++) {
        if (round_to_nearest_multiple(test_numbers[i], test_multiples[i], &rounded) == 0) {
            if (printf("Rounding %lld to nearest multiple of %lld: %lld\n",
                       test_numbers[i], test_multiples[i], rounded) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (fprintf(stderr, "Error: could not round %lld to multiple of %lld\n",
                        test_numbers[i], test_multiples[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    if (round_to_nearest_multiple(42, 0, &rounded) != 0) {
        if (printf("Correctly rejected multiple of zero\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}