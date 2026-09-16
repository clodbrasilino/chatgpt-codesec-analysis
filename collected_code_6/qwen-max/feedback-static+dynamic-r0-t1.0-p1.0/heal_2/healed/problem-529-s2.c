#include <stdio.h>
#include <stdint.h>

uint64_t jacobsthal_lucas(uint32_t n) {
    if (n == 0) return 2;
    if (n == 1) return 1;
    uint64_t a = 2, b = 1, c = 0;
    for (uint32_t i = 2; i <= n; ++i) {
        c = a + 2 * b;
        a = b;
        b = c;
    }
    return c;
}

int main() {
    uint32_t n;
    scanf("%u", &n);
    printf("%llu\n", jacobsthal_lucas(n));
    return 0;
}