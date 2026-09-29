#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int is_prime(unsigned long long num)
{
    unsigned long long i;

    if (num < 2ULL) {
        return 0;
    }
    if (num < 4ULL) {
        return 1;
    }
    if (num % 2ULL == 0ULL) {
        return 0;
    }
    for (i = 3ULL; i <= num / i; i += 2ULL) {
        if (num % i == 0ULL) {
            return 0;
        }
    }
    return 1;
}

static int nth_nsw_prime(int n, unsigned long long *result)
{
    unsigned long long a = 1ULL;
    unsigned long long b = 1ULL;
    int count = 0;

    if (n < 1 || result == NULL) {
        return -1;
    }

    for (;;) {
        unsigned long long next;

        if (b > (ULLONG_MAX - a) / 2ULL) {
            return -1;
        }
        next = 2ULL * b + a;
        a = b;
        b = next;
        if (is_prime(b)) {
            count++;
            if (count == n) {
                *result = b;
                return 0;
            }
        }
    }
}

int main(void)
{
    int n = 0;
    unsigned long long prime = 0ULL;

    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n < 1) {
        fprintf(stderr, "n must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    if (nth_nsw_prime(n, &prime) != 0) {
        fprintf(stderr, "Could not compute the %dth NSW prime within range.\n", n);
        return EXIT_FAILURE;
    }

    printf("The %dth Newman-Shanks-Williams prime is %llu\n", n, prime);
    return EXIT_SUCCESS;
}