#include <stdio.h>
#include <stdbool.h>

bool is_prime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

long long sum_of_primes(int n) {
    if (n < 2) return 0;
    long long sum = 0;
    for (int i = 2; i <= n; i++) {
        if (is_prime(i)) {
            sum += i;
        }
    }
    return sum;
}

int main(void) {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    if (n < 1) {
        printf("Number must be positive.\n");
        return 1;
    }
    printf("Sum of primes between 1 and %d: %lld\n", n, sum_of_primes(n));
    return 0;
}