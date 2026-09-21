#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_power_digits(unsigned int base, unsigned int exponent,
                            unsigned long long *result)
{
    if (result == NULL) {
        return -1;
    }

    size_t digits = 1;
    unsigned int *number = malloc(sizeof(*number));

    if (number == NULL) {
        return -1;
    }

    number[0] = 1;

    for (unsigned int e = 0; e < exponent; ++e) {
        unsigned long long carry = 0;

        for (size_t i = 0; i < digits; ++i) {
            unsigned long long value =
                (unsigned long long)number[i] * base + carry;

            number[i] = (unsigned int)(value % 10);
            carry = value / 10;
        }

        while (carry != 0) {
            if (digits == SIZE_MAX ||
                digits + 1 > SIZE_MAX / sizeof(*number)) {
                free(number);
                return -1;
            }

            size_t new_count = digits + 1;
            unsigned int *resized =
                realloc(number, new_count * sizeof(*number));

            if (resized == NULL) {
                free(number);
                return -1;
            }

            number = resized;
            number[digits] = (unsigned int)(carry % 10);
            digits = new_count;
            carry /= 10;
        }
    }

    unsigned long long sum = 0;

    for (size_t i = 0; i < digits; ++i) {
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

static int parse_unsigned_int(const char *text, unsigned int *value)
{
    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return -1;
    }

    errno = 0;
    char *end = NULL;
    unsigned long parsed = strtoul(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > UINT_MAX) {
        return -1;
    }

    *value = (unsigned int)parsed;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    const char *program = "program";

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program = argv[0];
    }

    if (argc != 3 || argv == NULL) {
        fprintf(stderr, "Usage: %s <base> <exponent>\n", program);
        return EXIT_FAILURE;
    }

    unsigned int base;
    unsigned int exponent;

    if (parse_unsigned_int(argv[1], &base) != 0) {
        fputs("Invalid base\n", stderr);
        return EXIT_FAILURE;
    }

    if (parse_unsigned_int(argv[2], &exponent) != 0) {
        fputs("Invalid exponent\n", stderr);
        return EXIT_FAILURE;
    }

    unsigned long long sum;

    if (sum_power_digits(base, exponent, &sum) != 0) {
        fputs("Unable to calculate the digit sum\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}