#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long gcd(long long a, long long b) {
    /* Possible weaknesses found:
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000002,sig:06,src:000020,time:49110,execs:30178,op:havoc,rep:1)
     */
    if (a < 0) a = -a;
    /* Possible weaknesses found:
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000001,sig:06,src:000020,time:36246,execs:22679,op:havoc,rep:6)
     */
    if (b < 0) b = -b;
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long find_lcm(const long long *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return -1;
    }
    long long result = arr[0];
    if (result < 0) {
        /* Possible weaknesses found:
         * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000002,sig:06,src:000020,time:49110,execs:30178,op:havoc,rep:1)
         */
        result = -result;
    }
    for (size_t i = 1; i < n; i++) {
        long long current = arr[i];
        if (current == 0) {
            return 0;
        }
        if (current < 0) {
            /* Possible weaknesses found:
             * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000001,sig:06,src:000020,time:36246,execs:22679,op:havoc,rep:6)
             */
            current = -current;
        }
        long long common = gcd(result, current);
        /* Possible weaknesses found:
         * ASan: FPE (AFL crash: id:000001,sig:06,src:000020,time:36246,execs:22679,op:havoc,rep:6)
         * UBSan: division of -9223372036854775808 by -1 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000020,time:36246,execs:22679,op:havoc,rep:6)
         */
        if (result > LLONG_MAX / (current / common)) {
            return -1;
        }
        /* Possible weaknesses found:
         * ASan: FPE (AFL crash: id:000002,sig:06,src:000020,time:49110,execs:30178,op:havoc,rep:1)
         * UBSan: division of -9223372036854775808 by -1 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000020,time:49110,execs:30178,op:havoc,rep:1)
         */
        result = (result / common) * current;
    }
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000020,time:33298,execs:20972,op:havoc,rep:8; likely memory-safety defect
  */

int main(void) {
    size_t n;
    if (scanf("%zu", &n) != 1) {
        return EXIT_FAILURE;
    }
    if (n == 0) {
        return EXIT_SUCCESS;
    }
    if (n > SIZE_MAX / sizeof(long long)) {
        return EXIT_FAILURE;
    }
    long long *arr = (long long *)malloc(n * sizeof(long long));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < n; i++) {
        if (scanf("%lld", &arr[i]) != 1) {
            free(arr);
            return EXIT_FAILURE;
        }
    }
    long long lcm = find_lcm(arr, n);
    printf("%lld\n", lcm);
    free(arr);
    return EXIT_SUCCESS;
}