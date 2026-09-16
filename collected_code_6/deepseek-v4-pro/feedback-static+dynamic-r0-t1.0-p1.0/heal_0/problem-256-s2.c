#include <stdio.h>
#include <stdbool.h>

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int count_primes(int n) {
    int count = 0;
    for (int i = 2; i < n; i++) {
        if (is_prime(i)) count++;
    }
    return count;
}

int main() {
    int num = 20;
    printf("Number of primes less than %d: %d\n", num, count_primes(num));
    return 0;
}