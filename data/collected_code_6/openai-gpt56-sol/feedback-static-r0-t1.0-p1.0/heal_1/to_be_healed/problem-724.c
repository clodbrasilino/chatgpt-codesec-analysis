#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int digit_sum_of_power(unsigned int base, unsigned int exponent,
                              unsigned long long *sum)
{
    size_t capacity = 1;
    size_t length = 1;
    unsigned char *digits = malloc(capacity);

    if (digits == NULL || sum == NULL) {
        free(digits);
        return -1;
    }

    digits[0] = 1;

    for (unsigned int power = 0; power < exponent; ++power) {
        unsigned long long carry = 0;

        for (size_t i = 0; i < length; ++i) {
            unsigned long long value =
                (unsigned long long)digits[i] * base + carry;
            digits[i] = (unsigned char)(value % 10U);
            carry = value / 10U;
        }

        while (carry != 0U) {
            if (length == capacity) {
                if (capacity > SIZE_MAX / 2U) {
                    free(digits);
                    return -1;
                }

                size_t new_capacity = capacity * 2U;
                unsigned char *new_digits = realloc(digits, new_capacity);

                if (new_digits == NULL) {
                    free(digits);
                    return -1;
                }

                digits = new_digits;
                capacity = new_capacity;
            }

            digits[length++] = (unsigned char)(carry % 10U);
            carry /= 10U;
        }
    }

    unsigned long long result = 0;

    for (size_t i = 0; i < length; ++i) {
        if (result > ULLONG_MAX - digits[i]) {
            free(digits);
            return -1;
        }

        result += digits[i];
    }

    free(digits);
    *sum = result;
    return 0;
}

static int parse_unsigned(const char *text, unsigned int *value)
{
    char *end = NULL;

    if (text == NULL || value == NULL || text[0] == '\0' || text[0] == '-') {
        return -1;
    }

    errno = 0;
    unsigned long parsed = strtoul(text, &end, 10);

    if (errno == ERANGE || *end != '\0' || parsed > UINT_MAX) {
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
    unsigned int base;
    unsigned int exponent;
    unsigned long long sum;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <base> <exponent>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_unsigned(argv[1], &base) != 0 ||
        parse_unsigned(argv[2], &exponent) != 0) {
        fprintf(stderr, "Base and exponent must be nonnegative integers.\n");
        return EXIT_FAILURE;
    }

    if (digit_sum_of_power(base, exponent, &sum) != 0) {
        fprintf(stderr, "Unable to calculate the digit sum.\n");
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}