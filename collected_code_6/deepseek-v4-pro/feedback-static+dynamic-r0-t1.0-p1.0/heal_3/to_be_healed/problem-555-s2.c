#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t sum_of_cubes_minus_sum(int64_t n) {
    if (n < 1) {
        return 0;
    }
    if (n > 28783) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000000,time:226,execs:160,op:havoc,rep:14)
         * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000000,time:226,execs:160,op:havoc,rep:14)
         * UBSan: signed integer overflow: 10000000010 * 10000000011 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000004,time:516,execs:338,op:havoc,rep:6)
         */
        int64_t sum = n * (n + 1) / 2;
        int64_t sum_cubes = 0;
        for (int64_t i = 1; i <= n; i++) {
            int64_t term = i * i;
            if (term > INT64_MAX / i) {
                return -1;
            }
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 9223193340756366400 + 473384830201856 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000000,time:226,execs:160,op:havoc,rep:14)
             */
            sum_cubes += term * i;
        }
        return sum_cubes - sum;
    }
    int64_t sum = n * (n + 1) / 2;
    int64_t sum_cubes = sum * sum;
    return sum_cubes - sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000002,sig:06,src:000005,time:708,execs:455,op:havoc,rep:3; likely memory-safety defect
  */

int main(void) {
    int64_t n;
    printf("Enter a positive integer: ");
    if (scanf("%" SCNd64, &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    int64_t result = sum_of_cubes_minus_sum(n);
    if (result == -1 && n > 28783) {
        printf("Overflow detected\n");
        return 1;
    }
    printf("%" PRId64 "\n", result);
    return 0;
}