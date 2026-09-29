#include <stdio.h>
#include <stdlib.h>

static long long compute_gcd(long long a, long long b)
{
    while (b != 0LL) {
        long long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

static int find_min_periodic(long long a, long long b, long long *result)
{
    if (b <= 0LL || a < 0LL || result == NULL) {
        return -1;
    }
    *result = compute_gcd(a, b) % b;
    return 0;
}

int main(void)
{
    long long a = 0LL;
    long long b = 0LL;
    long long minimum = 0LL;
    int status = 0;

    printf("Enter A and B: ");
    if (scanf("%lld %lld", &a, &b) != 2) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    status = find_min_periodic(a, b, &minimum);
    if (status != 0) {
        fprintf(stderr, "Error: A must be non-negative and B must be positive\n");
        return EXIT_FAILURE;
    }

    printf("Minimum possible value of (A * x) mod B is: %lld\n", minimum);

    return EXIT_SUCCESS;
}