#include <stdio.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 5, got 4
  *  test case 2 failed: expected 17, got 22
  *  test case 0 failed: expected 31, got 53
  */

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
     *  Uninitialized variable: c [uninitvar]
     *  Uninitialized variable: c
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