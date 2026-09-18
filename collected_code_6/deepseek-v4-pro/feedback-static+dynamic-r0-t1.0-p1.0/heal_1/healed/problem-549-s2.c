#include <stdio.h>
#include <stdint.h>

long long sum_fifth_power_odd(int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        long long odd = 2LL * i + 1;
        long long odd2 = odd * odd;
        long long odd4 = odd2 * odd2;
        sum += odd4 * odd;
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
    printf("Sum = %lld\n", sum_fifth_power_odd(n));
    return 0;
}