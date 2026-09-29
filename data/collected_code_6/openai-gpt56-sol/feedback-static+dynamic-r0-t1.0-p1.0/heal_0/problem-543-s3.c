#include <stdio.h>
#include <stdlib.h>

static int add_numbers(int a, int b, int *sum)
{
    if (sum == NULL) {
        return 0;
    }

    if (__builtin_add_overflow(a, b, sum)) {
        return 0;
    }

    return 1;
}

static size_t count_digits(int value)
{
    long long number = value;
    size_t digits = 0;

    if (number < 0) {
        number = -number;
    }

    do {
        ++digits;
        number /= 10;
    } while (number != 0);

    return digits;
}

int main(void)
{
    int first;
    int second;
    int sum;

    if (scanf("%d %d", &first, &second) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!add_numbers(first, second, &sum)) {
        fputs("Integer overflow\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Sum: %d\n", sum);
    printf("Number of digits: %zu\n", count_digits(sum));

    return EXIT_SUCCESS;
}