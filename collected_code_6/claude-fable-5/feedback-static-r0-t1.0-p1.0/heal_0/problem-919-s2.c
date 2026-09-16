#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>

bool multiply_list(const long *items, size_t count, long *result)
{
    if (items == NULL || result == NULL || count == 0U) {
        return false;
    }

    long product = 1L;

    for (size_t i = 0U; i < count; i++) {
        long value = items[i];

        if (value == 0L) {
            product = 0L;
            continue;
        }

        if (product > 0L) {
            if (value > 0L) {
                if (product > LONG_MAX / value) {
                    return false;
                }
            } else {
                if (value < LONG_MIN / product) {
                    return false;
                }
            }
        } else if (product < 0L) {
            if (value > 0L) {
                if (product < LONG_MIN / value) {
                    return false;
                }
            } else {
                if (product < LONG_MAX / value) {
                    return false;
                }
            }
        }

        product *= value;
    }

    *result = product;
    return true;
}

int main(void)
{
    long numbers[] = { 2L, 3L, 4L, 5L };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long result = 0L;

    if (!multiply_list(numbers, count, &result)) {
        if (fprintf(stderr, "Error: multiplication failed or overflowed\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Product: %ld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}