#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static long long gcd(long long a, long long b)
{
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

static long long lcm(long long a, long long b)
{
    if (a == 0 || b == 0) {
        return 0;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 219060189739591200 * 43 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:257,execs:136,op:havoc,rep:12)
     */
    return (a / gcd(a, b)) * b;
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
        result = lcm(result, (long long)i);
        if (result < 0) {
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