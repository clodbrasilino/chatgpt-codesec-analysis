#include <stdio.h>
#include <stdbool.h>

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

void identify_non_primes(int limit) {
    for (int i = 0; i <= limit; ++i) {
        if (!is_prime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int limit = 20;
    identify_non_primes(limit);
    return 0;
}