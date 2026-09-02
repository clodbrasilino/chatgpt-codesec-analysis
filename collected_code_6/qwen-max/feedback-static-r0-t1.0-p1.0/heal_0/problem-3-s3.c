#include <stdio.h>
#include <stdbool.h>

bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

void find_non_primes(int start, int end) {
    for (int i = start; i <= end; i++) {
        if (!is_prime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int start = 1;
    int end = 50;
    find_non_primes(start, end);
    return 0;
}