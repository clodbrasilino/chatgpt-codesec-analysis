#include <stdio.h>
#include <stdlib.h>

static unsigned long long digitSum(unsigned long long n)
{
    unsigned long long sum = 0ULL;

    while (n > 0ULL) {
        sum += n % 10ULL;
        n /= 10ULL;
    }

    return sum;
}

static unsigned long long maxDigitSumSplit(unsigned long long n,
                                           unsigned long long *partA,
                                           unsigned long long *partB)
{
    unsigned long long a = 0ULL;

    if ((partA == NULL) || (partB == NULL)) {
        return 0ULL;
    }

    while ((a * 10ULL + 9ULL) <= n) {
        a = a * 10ULL + 9ULL;
    }

    *partA = a;
    *partB = n - a;

    return digitSum(a) + digitSum(n - a);
}

int main(void)
{
    unsigned long long n = 0ULL;
    unsigned long long a = 0ULL;
    unsigned long long b = 0ULL;
    unsigned long long best = 0ULL;

    printf("Enter a non-negative number: ");

    if (scanf("%llu", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    best = maxDigitSumSplit(n, &a, &b);

    printf("Number: %llu\n", n);
    printf("Part A: %llu\n", a);
    printf("Part B: %llu\n", b);
    printf("Maximum digit sum: %llu\n", best);

    return EXIT_SUCCESS;
}