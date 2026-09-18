#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_prime(int num) {
    if (num < 2) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    for (int i = 3; i * i <= num && i * i > 0; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

int sum_of_primes(int n) {
    long long sum = 0;
    for (int i = 2; i <= n; i++) {
        if (is_prime(i)) {
            if (sum > INT_MAX - i) {
                return -1;
            }
            sum += i;
        }
    }
    return (int)sum;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    if (n < 1) {
        return 1;
    }
    if (n > 46340) {
        return 1;
    }
    int result = sum_of_primes(n);
    if (result == -1) {
        return 1;
    }
    printf("Sum of primes: %d\n", result);
    return 0;
}