#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>

int64_t gcd(int64_t a, int64_t b) {
    while (b != 0) {
        int64_t t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int64_t lcm(int64_t a, int64_t b) {
    if (a == 0 || b == 0) return 0;
    if (a >= LLONG_MAX / b) return 0; // Avoid overflow
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 7777777777777777 * -7777777777777776 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000011,time:13093,execs:5829,op:havoc,rep:3)
     */
    return (a / gcd(a, b)) * b;
}

int find_numbers_in_range(int64_t lower, int64_t upper) {
    for (int64_t i = lower; i <= upper; i++) {
        for (int64_t j = i + 1; j <= upper; j++) {
            int64_t result = lcm(i, j);
            if (result >= lower && result <= upper) {
                printf("Found numbers: %" PRId64 " and %" PRId64 "\n", i, j);
                return 0;
            }
        }
    }
    return -1;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000011,time:12907,execs:5745,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    int64_t lower, upper;

    printf("Enter the lower and upper bounds of the range: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64 " %" SCNd64, &lower, &upper) != 2) {
        printf("Invalid input.\n");
        return 1;
    }

    if (find_numbers_in_range(lower, upper) == -1) {
        printf("No such numbers found in the given range.\n");
    }

    return 0;
}