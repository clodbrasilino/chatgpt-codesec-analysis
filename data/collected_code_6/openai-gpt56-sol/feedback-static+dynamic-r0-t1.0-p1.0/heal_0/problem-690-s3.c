#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <errno.h>

static bool multiply_consecutive(const int64_t *values, size_t count, int64_t *result)
{
    int64_t product = 1;

    if (values == NULL || result == NULL || count == 0) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        if (__builtin_mul_overflow(product, values[i], &product)) {
            return false;
        }
    }

    *result = product;
    return true;
}

int main(void)
{
    int64_t values[] = {2, 3, 4, 5};
    int64_t result = 0;
    size_t count = sizeof(values) / sizeof(values[0]);

    errno = 0;

    if (!multiply_consecutive(values, count, &result)) {
        if (fputs("Multiplication failed.\n", stderr) == EOF) {
            return 2;
        }
        return 1;
    }

    if (printf("Product: %" PRId64 "\n", result) < 0) {
        return 2;
    }

    return 0;
}