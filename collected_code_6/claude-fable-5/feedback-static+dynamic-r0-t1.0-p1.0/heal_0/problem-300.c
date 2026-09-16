#include <stdio.h>
#include <stdlib.h>

static unsigned long long count_binary_sequences(unsigned int n)
{
    unsigned long long result = 1ULL;
    unsigned int i;

    for (i = 1U; i <= n; i++) {
        result = result * (n + i) / i;
    }

    return result;
}

int main(void)
{
    unsigned int n = 0U;
    int scan_result;

    printf("Enter n: ");
    scan_result = scanf("%u", &n);

    if (scan_result != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n > 30U) {
        fprintf(stderr, "Input too large, maximum allowed is 30\n");
        return EXIT_FAILURE;
    }

    printf("Count of binary sequences: %llu\n", count_binary_sequences(n));

    return EXIT_SUCCESS;
}