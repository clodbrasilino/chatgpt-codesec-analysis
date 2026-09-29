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
            size_t new_count;
            unsigned int *resized;

            if (digits == SIZE_MAX ||
                digits + 1U > SIZE_MAX / sizeof(*number)) {
                free(number);
                return -1;
            }

            new_count = digits + 1U;
            resized = realloc(number, new_count * sizeof(*number));
            if (resized == NULL) {
                free(number);
                return -1;
            }

            number = resized;
            number[digits] = (unsigned int)(carry % 10ULL);
            digits = new_count;
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

int main(int argc, char *const argv[])
{
    const char *const base_text = argc > 1 ? argv[1] : NULL;
    const char *const exponent_text = argc > 2 ? argv[2] : NULL;
    char *base_end = NULL;
    char *exponent_end = NULL;
    unsigned long base_value;
    unsigned long exponent_value;
    unsigned long long sum;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <base> <exponent>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    errno = 0;
    base_value = strtoul(base_text, &base_end, 10);

    if (errno != 0 || base_end == base_text || *base_end != '\0' ||
        base_value > UINT_MAX) {
        fputs("Invalid base\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    exponent_value = strtoul(exponent_text, &exponent_end, 10);

    if (errno != 0 || exponent_end == exponent_text ||
        *exponent_end != '\0' || exponent_value > UINT_MAX) {
        fputs("Invalid exponent\n", stderr);
        return EXIT_FAILURE;
    }

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