#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

bool is_prime(uint64_t n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (uint64_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

uint64_t ns_williams_prime(uint64_t n) {
    uint64_t a = 1, b = 1, c = 1, count = 0;
    while (true) {
        c = 2 * b + a;
        a = b;
        b = c;
        if (is_prime(c)) {
            count++;
            if (count == n) {
                return c;
            }
        }
    }
}

int main() {
    uint64_t n;
    printf("Enter the nth Newman–Shanks–Williams prime number to find: ");
    scanf("%lu", &n);
    uint64_t result = ns_williams_prime(n);
    printf("The %lu-th Newman–Shanks–Williams prime number is: %lu\n", n, result);
    return 0;
}