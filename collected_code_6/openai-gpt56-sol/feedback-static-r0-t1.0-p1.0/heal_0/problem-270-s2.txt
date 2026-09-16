#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

static int sum_even_at_even_positions(const int *values, size_t count, int64_t *sum)
{
    size_t i;
    int64_t result = 0;

    if (sum == NULL || (values == NULL && count != 0U)) {
        return -1;
    }

    for (i = 0U; i < count; i += 2U) {
        if (values[i] % 2 == 0) {
            result += values[i];
        }
    }

    *sum = result;
    return 0;
}

int main(void)
{
    int values[] = {2, 7, 4, 9, 6, 11, 8};
    const size_t count = sizeof(values) / sizeof(values[0]);
    int64_t sum;

    if (sum_even_at_even_positions(values, count, &sum) != 0) {
        fputs("Failed to calculate the sum.\n", stderr);
        return 1;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        return 1;
    }

    return 0;
}