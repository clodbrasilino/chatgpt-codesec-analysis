#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <limits.h>

static bool multiply_checked(long long a, long long b, long long *result)
{
    if (result == NULL) {
        return false;
    }

    if ((a > 0 && b > 0 && a > LLONG_MAX / b) ||
        (a > 0 && b < 0 && b < LLONG_MIN / a) ||
        (a < 0 && b > 0 && a < LLONG_MIN / b) ||
        (a < 0 && b < 0 && a < LLONG_MAX / b)) {
        return false;
    }

    *result = a * b;
    return true;
}

static bool product_of_non_repeated(const int array[], size_t length, long long *product)
{
    if (array == NULL || product == NULL || length == 0U) {
        return false;
    }

    long long result = 1;
    bool found = false;

    for (size_t i = 0U; i < length; ++i) {
        bool repeated = false;

        for (size_t j = 0U; j < length; ++j) {
            if (i != j && array[i] == array[j]) {
                repeated = true;
                break;
            }
        }

        if (!repeated) {
            if (!multiply_checked(result, array[i], &result)) {
                return false;
            }
            found = true;
        }
    }

    if (!found) {
        return false;
    }

    *product = result;
    return true;
}

int main(void)
{
    const int array[] = {2, 3, 4, 3, 5, 2, 6};
    const size_t length = sizeof(array) / sizeof(array[0]);
    long long product = 0;

    if (!product_of_non_repeated(array, length, &product)) {
        if (fputs("Unable to calculate the product.\n", stderr) == EOF) {
            return 2;
        }
        return 1;
    }

    if (printf("%lld\n", product) < 0) {
        return 2;
    }

    return 0;
}