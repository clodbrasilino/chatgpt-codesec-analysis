#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int multiply_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((a == -1 && b == INT64_MIN) || (b == -1 && a == INT64_MIN)) {
        return 0;
    }

    if (a > 0) {
        if ((b > 0 && a > INT64_MAX / b) ||
            (b < 0 && b < INT64_MIN / a)) {
            return 0;
        }
    } else if (a < 0) {
        if ((b > 0 && a < INT64_MIN / b) ||
            (b < 0 && a < INT64_MAX / b)) {
            return 0;
        }
    }

    *result = a * b;
    return 1;
}

static int product_of_non_repeated(const int64_t array[],
                                   size_t length,
                                   int64_t *product)
{
    int64_t value = 1;
    int found = 0;

    if ((array == NULL && length != 0U) || product == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t occurrences = 0;

        for (size_t j = 0; j < length; ++j) {
            if (array[i] == array[j]) {
                ++occurrences;
            }
        }

        if (occurrences == 1U) {
            if (!multiply_checked(value, array[i], &value)) {
                return 0;
            }
            found = 1;
        }
    }

    *product = found ? value : 0;
    return 1;
}

int main(void)
{
    int64_t array[] = {2, 3, 2, 4, 5, 5};
    const size_t length = sizeof array / sizeof array[0];
    int64_t product;

    if (!product_of_non_repeated(array, length, &product)) {
        if (fputs("Unable to calculate product.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    errno = 0;
    if (printf("%" PRId64 "\n", product) < 0 || errno != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}