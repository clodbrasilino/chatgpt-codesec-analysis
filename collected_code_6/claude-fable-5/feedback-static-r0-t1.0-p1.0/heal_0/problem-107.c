#include <stdio.h>
#include <stdlib.h>

static int has_hex_letter(unsigned long long n)
{
    while (n > 0ULL) {
        if ((n % 16ULL) > 9ULL) {
            return 1;
        }
        n /= 16ULL;
    }
    return 0;
}

static unsigned long long count_hex_numbers(unsigned long long low,
                                            unsigned long long high)
{
    unsigned long long count = 0ULL;
    unsigned long long i = low;

    for (;;) {
        if (has_hex_letter(i)) {
            count++;
        }
        if (i == high) {
            break;
        }
        i++;
    }
    return count;
}

int main(void)
{
    unsigned long long low;
    unsigned long long high;
    unsigned long long result;

    printf("Enter range (low high): ");

    if (scanf("%llu %llu", &low, &high) != 2) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (low > high) {
        fprintf(stderr, "Error: low must not exceed high\n");
        return EXIT_FAILURE;
    }

    result = count_hex_numbers(low, high);

    if (printf("Count: %llu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}