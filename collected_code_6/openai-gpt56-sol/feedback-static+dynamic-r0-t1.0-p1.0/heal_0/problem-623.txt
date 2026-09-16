#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int checked_power(long long base, unsigned int exponent, long long *result)
{
    long long value = 1;
    long long factor = base;

    if (result == NULL) {
        return 0;
    }

    while (exponent > 0U) {
        if ((exponent & 1U) != 0U) {
            if (__builtin_mul_overflow(value, factor, &value)) {
                return 0;
            }
        }

        exponent >>= 1U;

        if (exponent > 0U) {
            if (__builtin_mul_overflow(factor, factor, &factor)) {
                return 0;
            }
        }
    }

    *result = value;
    return 1;
}

static int power_elements(const long long *input, long long *output,
                          size_t count, unsigned int exponent)
{
    size_t i;

    if ((count > 0U) && (input == NULL || output == NULL)) {
        return 0;
    }

    for (i = 0U; i < count; ++i) {
        if (!checked_power(input[i], exponent, &output[i])) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    size_t count;
    unsigned int exponent;
    long long *input = NULL;
    long long *output = NULL;
    size_t i;
    int status = EXIT_FAILURE;

    if (scanf("%zu %u", &count, &exponent) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*input)) {
        fputs("List is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > 0U) {
        input = malloc(count * sizeof(*input));
        output = malloc(count * sizeof(*output));

        if (input == NULL || output == NULL) {
            fputs("Memory allocation failed\n", stderr);
            goto cleanup;
        }
    }

    for (i = 0U; i < count; ++i) {
        if (scanf("%lld", &input[i]) != 1) {
            fputs("Invalid list element\n", stderr);
            goto cleanup;
        }
    }

    if (!power_elements(input, output, count, exponent)) {
        fputs("Arithmetic overflow\n", stderr);
        goto cleanup;
    }

    for (i = 0U; i < count; ++i) {
        if (printf("%lld%c", output[i], i + 1U == count ? '\n' : ' ') < 0) {
            fputs("Output error\n", stderr);
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(output);
    free(input);
    return status;
}