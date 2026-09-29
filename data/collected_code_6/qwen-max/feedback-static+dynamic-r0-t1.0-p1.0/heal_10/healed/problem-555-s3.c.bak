#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

long long sum_of_cubes(long n) {
    if (n > 0x1FFFFF || n < -0x1FFFFF) return 0;
    if (n > 0 && LLONG_MAX / n / n < n + 1) return 0;
    if (n < 0 && LLONG_MIN / n / n > n + 1) return 0;
    int64_t temp = (n * (n + 1)) / 2;
    int64_t temp_sq = temp * temp;
    if (temp == 0) return 0;
    return temp_sq;
}

long long sum_of_numbers(long n) {
    if (n > 0x1FFFFF || n < -0x1FFFFF) return 0;
    if (n > 0 && LLONG_MAX / n < 2) return 0;
    if (n < 0 && LLONG_MIN / n > 2) return 0;
    int64_t temp = n * (n + 1);
    if (temp % 2 != 0) return 0;
    return temp / 2;
}

long long difference(long n) {
    return sum_of_cubes(n) - sum_of_numbers(n);
}

int main() {
    long n;
    printf("Enter a natural number: ");
    if (scanf("%ld", &n) != 1 || n < 1) {
        printf("Invalid input. Please enter a valid natural number.\n");
        return 1;
    }

    long long diff = difference(n);
    printf("The difference is: %lld\n", diff);
    return 0;
}