#include <stdio.h>
#include <stdint.h>
#include <limits.h>

unsigned long long sum_of_fifth_powers(int n) {
    if (n <= 0 || n > INT_MAX / 2) {
        return 0;
    }
    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long long temp = 2 * i;
        sum += temp * temp * temp * temp * temp;
    }
    return sum;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Enter a positive integer.\n");
        return 1;
    }
    unsigned long long result = sum_of_fifth_powers(n);
    printf("%llu\n", result);
    return 0;
}