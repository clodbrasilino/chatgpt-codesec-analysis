#include <stdio.h>
#include <stdlib.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long lcm(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b;
}

int find_two_numbers(long long lower, long long upper, long long *num1, long long *num2) {
    if (lower > upper || upper <= 0 || num1 == NULL || num2 == NULL) {
        return -1;
    }

    long long max_limit = upper > 1000000 ? 1000000 : upper;
    long long min_limit = lower < 1 ? 1 : lower;

    for (long long i = min_limit; i <= max_limit; i++) {
        for (long long j = i + 1; j <= max_limit; j++) {
            long long current_lcm = lcm(i, j);
            if (current_lcm >= lower && current_lcm <= upper) {
                *num1 = i;
                *num2 = j;
                return 0;
            }
        }
    }

    return -1;
}

int main(void) {
    long long lower, upper;
    long long num1, num2;

    printf("Enter lower bound: ");
    if (scanf("%lld", &lower) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter upper bound: ");
    if (scanf("%lld", &upper) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int result = find_two_numbers(lower, upper, &num1, &num2);
    if (result == 0) {
        printf("Found numbers: %lld and %lld with LCM %lld\n", num1, num2, lcm(num1, num2));
    } else {
        printf("No two distinct numbers found with LCM in range [%lld, %lld]\n", lower, upper);
    }

    return EXIT_SUCCESS;
}