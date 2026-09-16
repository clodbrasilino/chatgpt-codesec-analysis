#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_power_digits(unsigned int base, unsigned int exponent,
                            unsigned long long *result)
{
    size_t digits = 1U;
    unsigned int *number;

    if (result == NULL) {
        return -1;
    }

    number = calloc(digits, sizeof(*number));
    if (number == NULL) {
        return -1;
    }

    number[0] = 1U;

    for (unsigned int e = 0U; e < exponent; ++e) {
        unsigned long long carry = 0ULL;

        for (size_t i = 0U; i < digits; ++i) {
            unsigned long long value =
                (unsigned long long)number[i] * base + carry;

            number[i] = (unsigned int)(value % 10ULL);
            carry = value / 10ULL;
        }

        while (carry != 0ULL) {
            if (digits == SIZE_MAX ||
                digits + 1U > SIZE_MAX / sizeof(*number)) {
                free(number);
                return -1;
            }

            size_t new_count = digits + 1U;
            unsigned int *resized =
                realloc(number, new_count * sizeof(*number));

            if (resized == NULL) {
                free(number);
                return -1;
            }

            number = resized;
            number[digits++] = (unsigned int)(carry % 10ULL);
            carry /= 10ULL;
        }
    }

    unsigned long long sum = 0ULL;

    for (size_t i = 0U; i < digits; ++i) {
        if (sum > ULLONG_MAX - number[i]) {
            free(number);
            return -1;
        }

        sum += number[i];
    }

    free(number);
    *result = sum;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <base> <exponent>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *base_end = NULL;
    unsigned long base_value = strtoul(argv[1], &base_end, 10);

    if (errno != 0 || base_end == argv[1] || *base_end != '\0' ||
        base_value > UINT_MAX) {
        fputs("Invalid base\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *exponent_end = NULL;
    unsigned long exponent_value = strtoul(argv[2], &exponent_end, 10);

    if (errno != 0 || exponent_end == argv[2] || *exponent_end != '\0' ||
        exponent_value > UINT_MAX) {
        fputs("Invalid exponent\n", stderr);
        return EXIT_FAILURE;
    }

    unsigned long long sum;

    if (sum_power_digits((unsigned int)base_value,
                         (unsigned int)exponent_value, &sum) != 0) {
        fputs("Unable to calculate the digit sum\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}