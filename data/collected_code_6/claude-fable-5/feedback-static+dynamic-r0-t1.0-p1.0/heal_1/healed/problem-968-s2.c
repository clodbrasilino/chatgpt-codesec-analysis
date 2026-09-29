#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static unsigned long long compute_gcd(unsigned long long a, unsigned long long b)
{
    while (b != 0ULL) {
        unsigned long long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

static int max_periodic_value(long long a, long long b, long long *result)
{
    unsigned long long ua;
    unsigned long long ub;
    unsigned long long g;

    if (result == NULL) {
        return -1;
    }
    if (b <= 0LL) {
        return -1;
    }
    if (a < 0LL) {
        ua = (unsigned long long)(-(a + 1LL)) + 1ULL;
    } else {
        ua = (unsigned long long)a;
    }
    if (ua == 0ULL) {
        *result = 0LL;
        return 0;
    }
    ub = (unsigned long long)b;
    g = compute_gcd(ua, ub);
    *result = (long long)(ub - g);
    return 0;
}

int main(void)
{
    long long a = 0LL;
    long long b = 0LL;
    long long max_value = 0LL;

    printf("Enter A and B for f(x) = (A * x) mod B: ");

    if (scanf("%lld %lld", &a, &b) != 2) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (max_periodic_value(a, b, &max_value) != 0) {
        fprintf(stderr, "Error: B must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    printf("Maximum possible value of the periodic function: %lld\n", max_value);

    return EXIT_SUCCESS;
}