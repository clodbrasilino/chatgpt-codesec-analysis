#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <limits.h>

static bool multiply_all(const long long *items, size_t count, long long *result)
{
    if (items == NULL || result == NULL) {
        return false;
    }

    long long product = 1;

    for (size_t i = 0; i < count; ++i) {
        const long long value = items[i];

        if ((value > 0 && product > LLONG_MAX / value) ||
            (value < 0 && product > 0 && value < LLONG_MIN / product) ||
            (value < 0 && product < 0 && product < LLONG_MAX / value)) {
            return false;
        }

        product *= value;
    }

    *result = product;
    return true;
}

int main(void)
{
    const long long items[] = {2, 3, 4, 5};
    const size_t count = sizeof(items) / sizeof(items[0]);
    long long result = 0;

    if (!multiply_all(items, count, &result)) {
        fputs("Multiplication failed\n", stderr);
        return 1;
    }

    if (printf("%lld\n", result) < 0) {
        return 1;
    }

    return 0;
}