#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int integer_power(long long base, unsigned int exponent, long long *result)
{
    long long value = 1;

    if (result == NULL) {
        return 0;
    }

    while (exponent > 0U) {
        if ((exponent & 1U) != 0U) {
            if ((base > 0 && (value > LLONG_MAX / base || value < LLONG_MIN / base)) ||
                /* Possible weaknesses found:
                 * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000022,time:57657,execs:20000,op:havoc,rep:5)
                 */
                (base < 0 && (value == LLONG_MIN || -value > LLONG_MAX / -base))) {
                return 0;
            }
            value *= base;
        }

        exponent >>= 1U;

        if (exponent > 0U) {
            if ((base > 0 && base > LLONG_MAX / base) ||
                (base < 0 && base < LLONG_MAX / base)) {
                return 0;
            }
            base *= base;
        }
    }

    *result = value;
    return 1;
}

static int power_elements(const long long *input, long long *output,
                          size_t count, unsigned int exponent)
{
    size_t i;

    if ((count > 0U && (input == NULL || output == NULL))) {
        return 0;
    }

    for (i = 0U; i < count; ++i) {
        if (!integer_power(input[i], exponent, &output[i])) {
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
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*input)) {
        fprintf(stderr, "List is too large\n");
        return EXIT_FAILURE;
    }

    if (count > 0U) {
        input = malloc(count * sizeof(*input));
        output = malloc(count * sizeof(*output));

        if (input == NULL || output == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            goto cleanup;
        }
    }

    for (i = 0U; i < count; ++i) {
        if (scanf("%lld", &input[i]) != 1) {
            fprintf(stderr, "Invalid list element\n");
            goto cleanup;
        }
    }

    if (!power_elements(input, output, count, exponent)) {
        fprintf(stderr, "Arithmetic overflow\n");
        goto cleanup;
    }

    for (i = 0U; i < count; ++i) {
        if (printf("%lld%c", output[i], i + 1U == count ? '\n' : ' ') < 0) {
            fprintf(stderr, "Output error\n");
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    free(output);
    free(input);
    return status;
}