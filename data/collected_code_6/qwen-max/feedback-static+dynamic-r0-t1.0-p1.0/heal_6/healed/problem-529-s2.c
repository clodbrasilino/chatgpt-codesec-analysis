#include <stdio.h>
#include <stdint.h>

uint64_t jacobsthal_lucas(uint32_t n) {
    if (n == 0) return 2;
    if (n == 1) return 1;
    uint64_t a = 2, b = 1, c;
    for (uint32_t i = 2; i <= n; ++i) {
        c = 2 * a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    uint32_t n;
    if (scanf("%u", &n) != 1) {
        return 1;
    }
    printf("%llu\n", (unsigned long long)jacobsthal_lucas(n));
    return 0;
}