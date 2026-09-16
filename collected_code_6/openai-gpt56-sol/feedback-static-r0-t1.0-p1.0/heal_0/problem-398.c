#include <stdio.h>
#include <stdlib.h>

static unsigned long long sum_digits(long long number)
{
    unsigned long long value;
    unsigned long long sum = 0;

    if (number < 0) {
        value = 0ULL - (unsigned long long)number;
    } else {
        value = (unsigned long long)number;
    }

    do {
        sum += value % 10ULL;
        value /= 10ULL;
    } while (value != 0ULL);

    return sum;
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1) {
        fprintf(stderr, "Failed to read the number of elements.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        long long number;

        if (scanf("%lld", &number) != 1) {
            fprintf(stderr, "Failed to read element %zu.\n", i + 1);
            return EXIT_FAILURE;
        }

        printf("%llu%s", sum_digits(number), i + 1 == count ? "\n" : " ");
    }

    return EXIT_SUCCESS;
}