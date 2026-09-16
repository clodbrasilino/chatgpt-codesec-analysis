#include <stddef.h>
#include <stdio.h>

static long long sum_even_at_even_positions(const int values[], size_t length)
{
    long long sum = 0;

    for (size_t i = 1; i < length; i += 2) {
        if (values[i] % 2 == 0) {
            sum += values[i];
        }
    }

    return sum;
}

int main(void)
{
    int values[] = {1, 2, 3, 4, 5, 6};
    size_t length = sizeof values / sizeof values[0];
    long long sum = sum_even_at_even_positions(values, length);

    if (printf("%lld\n", sum) < 0) {
        return 1;
    }

    return 0;
}