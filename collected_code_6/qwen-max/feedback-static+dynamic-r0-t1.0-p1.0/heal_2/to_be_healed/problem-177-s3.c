#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

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
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -9223372036854775807 * -9223372036854775808 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000010,time:16849,execs:7214,op:havoc,rep:2)
     */
    return (a / gcd(a, b)) * b;
}

int find_numbers_in_range(int64_t lower, int64_t upper) {
    for (int64_t i = lower; i <= upper; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000010,time:16849,execs:7214,op:havoc,rep:2)
         */
        for (int64_t j = i + 1; j <= upper; j++) {
            int64_t result = lcm(i, j);
            if (result >= lower && result <= upper) {
                /* Possible weaknesses found:
                 *  %lld in format string (no. 2) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
                 *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
                 */
                printf("Found numbers: %lld and %lld\n", i, j);
                return 0;
            }
        }
    }
    return -1;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:545,execs:226,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int64_t lower, upper;

    printf("Enter the lower and upper bounds of the range: ");
    /* Possible weaknesses found:
     *  %lld in format string (no. 2) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
     *  %lld in format string (no. 1) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
     */
    if (scanf("%lld %lld", &lower, &upper) != 2) {
        printf("Invalid input.\n");
        return 1;
    }

    if (find_numbers_in_range(lower, upper) == -1) {
        printf("No such numbers found in the given range.\n");
    }

    return 0;
}