#include <stdio.h>
#include <stdint.h>

uint64_t jacobsthal_lucas(uint32_t n) {
    if (n == 0) return 2;
    if (n == 1) return 1;
    uint64_t a = 2, b = 1, c;
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (uint32_t i = 2; i <= n; ++i) {
        c = a + 2 * b;
        a = b;
        b = c;
    }
    /* Possible weaknesses found:
     *  Uninitialized variable: c
     *  Uninitialized variable: c [uninitvar]
     */
    return c;
}

int main() {
    uint32_t n;
    scanf("%u", &n);
    /* Possible weaknesses found:
     *  %llu in format string (no. 1) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     */
    printf("%llu\n", jacobsthal_lucas(n));
    return 0;
}