#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

int64_t gcd(int64_t a, int64_t b) {
    while (b != 0) {
        int64_t t = b;
        b = a % b;
        a = t;
    }
    return a;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 12, got <no output>
  *  test case 1 failed: expected 255, got <no output>
  *  test case 2 failed: expected 6, got <no output>
  */

int64_t lcm(int64_t a, int64_t b) {
    if (a == 0 || b == 0) return 0;
    if (a == INT64_MAX || b == INT64_MAX) return INT64_MAX;
    int64_t gcd_value = gcd(a, b);
    if (INT64_MAX / a < (b / gcd_value)) return INT64_MAX;
    return (a / gcd_value) * b;
}

int main() {
    int64_t x, y;
    printf("Enter two positive integers: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64 " %" SCNd64, &x, &y) == 2) {
        if (x > 0 && y > 0) {
            printf("LCM of %" PRId64 " and %" PRId64 " is %" PRId64 "\n", x, y, lcm(x, y));
        } else {
            printf("Please enter positive integers.\n");
        }
    } else {
        printf("Invalid input.\n");
    }
    return 0;
}