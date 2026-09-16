#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int is_power_of_two(unsigned long long x)
{
    if (x == 0ULL) {
        return 0;
    }
    return ((x & (x - 1ULL)) == 0ULL) ? 1 : 0;
}

static int nth_polite_number(unsigned long long n, unsigned long long *result)
{
    unsigned long long count = 0ULL;
    unsigned long long candidate = 0ULL;

    if (result == NULL || n == 0ULL) {
        return -1;
    }

    while (count < n) {
        if (candidate == ULLONG_MAX) {
            return -1;
        }
        candidate += 1ULL;
        if (!is_power_of_two(candidate)) {
            count += 1ULL;
        }
    }

    *result = candidate;
    return 0;
}

int main(void)
{
    unsigned long long n = 0ULL;
    unsigned long long answer = 0ULL;

    printf("Enter n: ");
    if (scanf("%llu", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n == 0ULL) {
        fprintf(stderr, "n must be greater than zero.\n");
        return EXIT_FAILURE;
    }

    if (nth_polite_number(n, &answer) != 0) {
        fprintf(stderr, "Computation failed.\n");
        return EXIT_FAILURE;
    }

    printf("The %llu-th polite number is %llu\n", n, answer);
    return EXIT_SUCCESS;
}