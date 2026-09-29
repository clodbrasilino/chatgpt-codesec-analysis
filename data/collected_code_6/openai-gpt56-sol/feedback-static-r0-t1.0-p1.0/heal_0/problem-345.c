#include <stdio.h>
#include <stddef.h>

static int print_consecutive_differences(const long long numbers[], size_t count)
{
    if (numbers == NULL || count < 2U) {
        return -1;
    }

    for (size_t i = 1U; i < count; ++i) {
        printf("%lld\n", numbers[i] - numbers[i - 1U]);
    }

    return 0;
}

int main(void)
{
    long long numbers[] = {10, 15, 12, 20, 25};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);

    if (print_consecutive_differences(numbers, count) != 0) {
        fputs("At least two numbers are required.\n", stderr);
        return 1;
    }

    return 0;
}