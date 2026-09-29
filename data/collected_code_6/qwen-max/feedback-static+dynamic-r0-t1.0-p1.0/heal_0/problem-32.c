#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

bool is_prime(uint64_t n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (uint64_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

uint64_t largest_prime_factor(uint64_t n) {
    uint64_t max_prime = -1;
    while (n % 2 == 0) {
        max_prime = 2;
        n /= 2;
    }
    for (uint64_t i = 3; i <= n / i; i += 2) {
        while (n % i == 0) {
            max_prime = i;
            n /= i;
        }
    }
    if (n > 2 && is_prime(n)) {
        max_prime = n;
    }
    return max_prime;
}

int main() {
    uint64_t number = 600851475143;
    printf("Largest prime factor is %" PRIu64 "\n", largest_prime_factor(number));
    return 0;
}