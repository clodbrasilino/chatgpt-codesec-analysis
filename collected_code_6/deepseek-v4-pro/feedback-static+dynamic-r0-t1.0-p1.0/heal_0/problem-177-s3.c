#include <stdio.h>
#include <stdlib.h>

static long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

static long long lcm(long long a, long long b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    long long g = gcd(a, b);
    return (a / g) * b;
}

int find_two_numbers_lcm_in_range(long long low, long long high) {
    if (low > high || low < 0 || high < 0) {
        return 0;
    }
    long long i, j;
    for (i = low; i <= high; i++) {
        for (j = i + 1; j <= high; j++) {
            long long l = lcm(i, j);
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
    if (!find_two_numbers_lcm_in_range(low, high)) {
        printf("No such pair found\n");
    }
    return EXIT_SUCCESS;
}