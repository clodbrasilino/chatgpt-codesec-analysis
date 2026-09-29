#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

static int largest_adjacent_product(const int *values, size_t count, int64_t *result)
{
    if (values == NULL || result == NULL || count < 2) {
        return -1;
    }

    int64_t largest = (int64_t)values[0] * values[1];

    for (size_t i = 1; i + 1 < count; ++i) {
        int64_t product = (int64_t)values[i] * values[i + 1];

        if (product > largest) {
            largest = product;
        }
    }

    *result = largest;
    return 0;
}

int main(void)
{
    const int values[] = {3, 6, -2, -5, 7, 3};
    const size_t count = sizeof(values) / sizeof(values[0]);
    int64_t result = 0;

    if (largest_adjacent_product(values, count, &result) != 0) {
        (void)fprintf(stderr, "Unable to calculate the largest adjacent product.\n");
        return 1;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        return 1;
    }

    return 0;
}