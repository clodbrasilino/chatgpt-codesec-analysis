#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_prime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

int sum_of_primes(int n) {
    int sum = 0;
    for (int i = 2; i <= n; i++) {
        if (is_prime(i)) {
            if (sum > INT_MAX - i) {
                printf("Integer overflow detected. Aborting.\n");
                return -1;
            }
            sum += i;
        }
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    while (scanf("%d", &n) != 1 || n < 1) {
        while (getchar() != '\n') {}
        printf("Invalid input. Please enter a positive integer.\n");
        printf("Enter a positive integer: ");
    }
    int result = sum_of_primes(n);
    if (result != -1) {
        printf("Sum of prime numbers between 1 and %d is: %d\n", n, result);
    }
    return 0;
}