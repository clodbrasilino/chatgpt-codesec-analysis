#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>

static int multiply_consecutive(const long *numbers, size_t count, long *products)
{
    size_t i;

    if (numbers == NULL || products == NULL || count < 2U) {
        return -1;
    }

    for (i = 0U; i + 1U < count; ++i) {
        long a = numbers[i];
        long b = numbers[i + 1U];

        if ((a > 0L && ((b > 0L && a > LONG_MAX / b) ||
                       (b < 0L && b < LONG_MIN / a))) ||
            (a < 0L && ((b > 0L && a < LONG_MIN / b) ||
                       (b < 0L && a < LONG_MAX / b)))) {
            return -2;
        }

        products[i] = a * b;
    }

    return 0;
}

int main(void)
{
    long numbers[] = {2L, 3L, 4L, 5L};
    long products[(sizeof(numbers) / sizeof(numbers[0])) - 1U];
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int result;
    size_t i;

    errno = 0;
    result = multiply_consecutive(numbers, count, products);

    if (result == -1) {
        fputs("Invalid argument.\n", stderr);
        return 1;
    }

    if (result == -2) {
        fputs("Multiplication overflow.\n", stderr);
        return 1;
    }

    for (i = 0U; i + 1U < count; ++i) {
        if (printf("%ld%s", products[i], (i + 2U < count) ? " " : "\n") < 0) {
            perror("printf");
            return 1;
        }
    }

    return 0;
}