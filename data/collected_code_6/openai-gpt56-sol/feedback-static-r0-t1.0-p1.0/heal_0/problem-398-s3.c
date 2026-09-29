#include <stdio.h>
#include <stdlib.h>

static unsigned int sum_digits(long long number)
{
    unsigned long long value;
    unsigned int sum = 0U;

    if (number < 0) {
        value = 0ULL - (unsigned long long)number;
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
        fprintf(stderr, "Failed to read the list size.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        long long number;

        if (scanf("%lld", &number) != 1) {
            fprintf(stderr, "Failed to read number %zu.\n", i + 1U);
            return EXIT_FAILURE;
        }

        printf("%u\n", sum_digits(number));
    }

    if (fflush(stdout) == EOF) {
        fprintf(stderr, "Failed to write output.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}