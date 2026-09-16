#include <stdio.h>
#include <stdlib.h>

static unsigned int sum_digits(long long number)
{
    unsigned long long value;
    unsigned int sum = 0U;

    if (number < 0) {
        value = (unsigned long long)(-(number + 1LL)) + 1ULL;
    } else {
        value = (unsigned long long)number;
    }

    do {
        sum += (unsigned int)(value % 10ULL);
        value /= 10ULL;
    } while (value != 0ULL);

    return sum;
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid list size.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        long long number;

        if (scanf("%lld", &number) != 1) {
            fputs("Invalid number.\n", stderr);
            return EXIT_FAILURE;
        }

        printf("%u\n", sum_digits(number));
    }

    if (ferror(stdout) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}