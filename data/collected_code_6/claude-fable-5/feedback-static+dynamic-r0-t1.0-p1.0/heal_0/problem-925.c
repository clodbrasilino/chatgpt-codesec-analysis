#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int product_of_tuple(const long long *numbers, size_t count, long long *result)
{
    size_t i;
    long long product;

    if (numbers == NULL || result == NULL || count == 0U) {
        return -1;
    }

    product = 1LL;

    for (i = 0U; i < count; i++) {
        long long value = numbers[i];

        if (value != 0LL) {
            if (product > 0LL) {
                if (value > 0LL) {
                    if (product > LLONG_MAX / value) {
                        return -2;
                    }
                } else {
                    if (value < LLONG_MIN / product) {
                        return -2;
                    }
                }
            } else if (product < 0LL) {
                if (value > 0LL) {
                    if (product < LLONG_MIN / value) {
                        return -2;
                    }
                } else {
                    if (product < LLONG_MAX / value) {
                        return -2;
                    }
                }
            }
        }

        product *= value;
    }

    *result = product;
    return 0;
}

int main(void)
{
    long long tuple[] = { 4LL, 3LL, 2LL, 2LL, -1LL, 18LL };
    size_t count = sizeof(tuple) / sizeof(tuple[0]);
    long long result = 0LL;
    int status;

    status = product_of_tuple(tuple, count, &result);

    if (status == 0) {
        if (printf("Product: %lld\n", result) < 0) {
            return EXIT_FAILURE;
        }
    } else if (status == -2) {
        if (fprintf(stderr, "Error: arithmetic overflow detected\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    } else {
        if (fprintf(stderr, "Error: invalid input\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}