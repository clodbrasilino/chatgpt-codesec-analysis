#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

static long long gcd(long long a, long long b)
{
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

static bool lcm(long long a, long long b, long long *result)
{
    if (a == 0 || b == 0) {
        *result = 0;
        return true;
    }
    
    long long g = gcd(a, b);
    long long temp = a / g;
    
    if (temp > LLONG_MAX / b) {
        return false;
    }
    
    *result = temp * b;
    return true;
}

long long smallest_multiple(int n)
{
    long long result;
    int i;

    if (n <= 0) {
        return 0;
    }

    result = 1;
    for (i = 2; i <= n; i++) {
        if (!lcm(result, (long long)i, &result)) {
            return -1;
        }
    }

    return result;
}

int main(void)
{
    int n;
    long long result;

    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n <= 0) {
        fprintf(stderr, "Error: n must be a positive integer\n");
        return EXIT_FAILURE;
    }

    result = smallest_multiple(n);
    if (result == -1) {
        fprintf(stderr, "Error: Overflow detected\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}