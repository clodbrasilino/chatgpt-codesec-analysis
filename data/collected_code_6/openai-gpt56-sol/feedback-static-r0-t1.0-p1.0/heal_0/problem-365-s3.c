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

    if (printf("Enter an integer: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%lld", &number) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (printf("Number of digits: %zu\n", count_digits(number)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}