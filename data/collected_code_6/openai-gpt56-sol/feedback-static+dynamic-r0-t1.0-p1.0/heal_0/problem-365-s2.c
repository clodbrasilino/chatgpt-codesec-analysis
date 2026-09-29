#include <stdio.h>
#include <stdlib.h>

static size_t count_digits(long long number)
{
    size_t count = 1;

    while (number <= -10 || number >= 10) {
        number /= 10;
        ++count;
    }

    return count;
}

int main(void)
{
    long long number;

    if (scanf("%lld", &number) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", count_digits(number));
    return EXIT_SUCCESS;
}