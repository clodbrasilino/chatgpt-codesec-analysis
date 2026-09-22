#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

bool is_prime(uint64_t n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (uint64_t i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}

uint64_t nth_newman_shanks_williams_prime(uint64_t n) {
    uint64_t a = 1, b = 1, index = 0;
    while (true) {
        uint64_t next = 2 * b + a;
        a = b;
        b = next;
        if (is_prime(next)) {
            index++;
            if (index == n) return next;
        }
    }
}

int main() {
    uint64_t n;
    scanf("%lu", &n);
    uint64_t result = nth_newman_shanks_williams_prime(n);
    printf("%lu\n", result);
    return 0;
}