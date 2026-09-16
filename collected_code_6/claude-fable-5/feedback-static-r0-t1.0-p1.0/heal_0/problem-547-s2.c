#include <stdio.h>
#include <stdlib.h>

static unsigned int hamming_distance(unsigned long long a, unsigned long long b)
{
    unsigned long long x = a ^ b;
    unsigned int count = 0U;

    while (x != 0ULL) {
        count += (unsigned int)(x & 1ULL);
        x >>= 1U;
    }

    return count;
}

static unsigned long long sum_hamming_distances(unsigned long long n)
{
    unsigned long long total = 0ULL;
    unsigned long long i;

    for (i = 0ULL; i < n; i++) {
        total += (unsigned long long)hamming_distance(i, i + 1ULL);
    }

    return total;
}

int main(void)
{
    unsigned long long n = 0ULL;
    int result;

    printf("Enter n: ");
    result = scanf("%llu", &n);

    if (result != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (n == 0ULL) {
        printf("Sum of hamming distances: 0\n");
        return EXIT_SUCCESS;
    }

    printf("Sum of hamming distances: %llu\n", sum_hamming_distances(n));

    return EXIT_SUCCESS;
}