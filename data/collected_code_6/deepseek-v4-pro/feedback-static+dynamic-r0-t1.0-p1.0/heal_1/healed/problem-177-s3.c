#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static long long gcd(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

static int safe_lcm(long long a, long long b, long long *result) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    if (a == 0 || b == 0) {
        *result = 0;
        return 1;
    }
    long long g = gcd(a, b);
    if (a > LLONG_MAX / (b / g)) {
        return 0;
    }
    *result = (a / g) * b;
    return 1;
}

int find_two_numbers_lcm_in_range(long long low, long long high) {
    if (low > high || low < 0 || high < 0) {
        return 0;
    }
    long long i, j;
    for (i = low; i <= high; i++) {
        for (j = i + 1; j <= high; j++) {
            long long l;
            if (!safe_lcm(i, j, &l)) {
                continue;
            }
            if (l >= low && l <= high) {
                printf("%lld %lld\n", i, j);
                return 1;
            }
        }
    }
    return 0;
}

int main(void) {
    long long low, high;
    if (scanf("%lld %lld", &low, &high) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (low < 0 || high < 0) {
        fprintf(stderr, "Inputs must be non-negative\n");
        return EXIT_FAILURE;
    }
    if (!find_two_numbers_lcm_in_range(low, high)) {
        printf("No such pair found\n");
    }
    return EXIT_SUCCESS;
}