#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

long gcd(long a, long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

bool safe_lcm(long a, long b, long *result) {
    long g = gcd(a, b);
    if (a / g > LONG_MAX / b)
        return false;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -9223372036854775807 * -9223372036854775808 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:12570,execs:5410,op:havoc,rep:4)
     */
    *result = (a / g) * b;
    return true;
}

int find_two_numbers_within_lcm_range(long l, long r) {
    for (long i = l; i <= r; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:12570,execs:5410,op:havoc,rep:4)
         */
        for (long j = i + 1; j <= r; j++) {
            long lcm_result;
            if (safe_lcm(i, j, &lcm_result) && lcm_result >= l && lcm_result <= r) {
                printf("Two numbers: %ld and %ld\n", i, j);
                return 1;
            }
        }
    }
    return 0;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:2678,execs:1151,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    long l, r;
    printf("Enter the range (l r): ");
    int ret = scanf("%ld %ld", &l, &r);
    if (ret != 2 || l > r) {
        fprintf(stderr, "Invalid input. Please enter two integers where the first is less than or equal to the second.\n");
        return EXIT_FAILURE;
    }

    if (find_two_numbers_within_lcm_range(l, r) == 0) {
        printf("No such pair found in the given range.\n");
    }

    return EXIT_SUCCESS;
}