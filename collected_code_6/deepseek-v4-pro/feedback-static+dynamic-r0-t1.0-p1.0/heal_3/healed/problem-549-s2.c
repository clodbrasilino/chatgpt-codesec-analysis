#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

long long sum_fifth_power_odd(int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        unsigned long long odd = 2ULL * i + 1;
        unsigned long long odd2 = odd * odd;
        unsigned long long odd4 = odd2 * odd2;
        unsigned long long term = odd4 * odd;
        if (term > (unsigned long long)LLONG_MAX) {
            return -1;
        }
        sum += (long long)term;
    }
    return sum;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid input\n");
        return 1;
    }
    if (n > 100000) {
        printf("Input too large\n");
        return 1;
    }
    long long result = sum_fifth_power_odd(n);
    if (result == -1 && n > 1000) {
        printf("Result too large to store in long long\n");
        return 1;
    }
    printf("Sum = %lld\n", result);
    return 0;
}