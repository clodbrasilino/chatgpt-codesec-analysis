#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

bool is_prime(uint64_t n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (uint64_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

uint64_t nswhelper(uint64_t m, uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t k) {
    if (k == 0) return a;
    return nswhelper(2 * m, (a * m - b) * m - 2 * c, a * b - 2 * d, b * b + 2 * c * m, b * c + d * m, k - 1);
}

uint64_t newman_shanks_williams(uint64_t n) {
    if (n == 0) return 7;
    if (n == 1) return 41;
    return nswhelper(2, 1, 1, 1, 1, n - 1);
}

int main() {
    uint64_t n;
    printf("Enter the index of the NSW prime: ");
    scanf("%lu", &n);

    uint64_t nsw_prime = newman_shanks_williams(n);
    if (is_prime(nsw_prime)) {
        printf("The %lu-th NSW prime is: %lu\n", n, nsw_prime);
    } else {
        printf("An error occurred in calculating the %lu-th NSW prime.\n", n);
    }

    return 0;
}