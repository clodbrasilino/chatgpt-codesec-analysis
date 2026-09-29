#include <stddef.h>
#include <stdio.h>

static int sum_even_at_even_positions(const int values[], size_t length, long long *result)
{
    size_t index;
    long long sum = 0;

    if (values == NULL || result == NULL) {
        return -1;
    }

    for (index = 0; index < length; index += 2) {
        if (values[index] % 2 == 0) {
            sum += values[index];
        }
    }

    *result = sum;
    return 0;
}

int main(void)
{
    const int values[] = {2, 3, 4, 6, 8, 9, 10};
    const size_t length = sizeof(values) / sizeof(values[0]);
    long long sum;

    if (sum_even_at_even_positions(values, length, &sum) != 0) {
        fputs("Failed to calculate the sum.\n", stderr);
        return 1;
    }

    if (printf("%lld\n", sum) < 0) {
        return 1;
    }

    return 0;
}