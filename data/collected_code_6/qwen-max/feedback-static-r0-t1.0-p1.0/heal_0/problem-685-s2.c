#include <stdio.h>
#include <stdbool.h>

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
            sum += i;
        }
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    int result = sum_of_primes(n);
    printf("Sum of prime numbers between 1 and %d is: %d\n", n, result);
    return 0;
}