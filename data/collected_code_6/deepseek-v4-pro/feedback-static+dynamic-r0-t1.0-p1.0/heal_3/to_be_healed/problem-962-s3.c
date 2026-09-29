#include <stdio.h>
#include <stdint.h>

int64_t sum_even_in_range(int64_t l, int64_t r) {
    if (l > r) {
        return 0;
    }
    if (l <= 0) {
        l = 1;
    }
    if (l % 2 != 0) {
        l++;
    }
    if (r % 2 != 0) {
        r--;
    }
    if (l > r) {
        return 0;
    }
    int64_t n = (r - l) / 2 + 1;
    if (n % 2 == 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2305843009213416174 * -9223372036853664698 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000004,sig:06,src:000004,time:58460,execs:36960,op:havoc,rep:5)
         * UBSan: signed integer overflow: 1111112 + 9223372036854775806 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000004,sig:06,src:000004,time:58460,execs:36960,op:havoc,rep:5)
         * UBSan: signed integer overflow: 13888875000 * 55555611110 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000006,time:27596,execs:17550,op:havoc,rep:3)
         */
        return (n / 2) * (l + r);
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4999999995 * 5000000000 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000006,time:5191,execs:3392,op:havoc,rep:1)
         * UBSan: signed integer overflow: 6 + 9223372036854775806 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000006,time:19258,execs:12379,op:havoc,rep:1)
         * UBSan: signed integer overflow: 4611686018427387901 * -4611686018427387902 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000006,time:19258,execs:12379,op:havoc,rep:1)
         */
        return n * ((l + r) / 2);
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000003,sig:06,src:000006,time:46765,execs:29563,op:havoc,rep:3; likely memory-safety defect
  */

int main(void) {
    long long l, r;
    printf("Enter lower bound: ");
    if (scanf("%lld", &l) != 1) {
        return 1;
    }
    printf("Enter upper bound: ");
    if (scanf("%lld", &r) != 1) {
        return 1;
    }
    long long result = sum_even_in_range(l, r);
    printf("Sum of even numbers in range [%lld, %lld]: %lld\n", l, r, result);
    return 0;
}