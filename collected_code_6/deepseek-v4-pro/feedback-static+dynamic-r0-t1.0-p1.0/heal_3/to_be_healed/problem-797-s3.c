#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int64_t sum_of_odd_numbers(int64_t l, int64_t r) {
    if (l > r) {
        return 0;
    }

    if (l % 2 == 0) {
        l++;
    }
    if (r % 2 == 0) {
        r--;
    }

    if (l > r) {
        return 0;
    }

    int64_t n = (r - l) / 2 + 1;

    if (n % 2 == 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 138888888888889 * 555555555555560 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000006,time:18457,execs:10626,op:havoc,rep:1)
         * UBSan: signed integer overflow: 5555555555555554 * 22222222222222228 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000005,time:26059,execs:14785,op:havoc,rep:7)
         */
        return (n / 2) * (l + r);
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 23 + 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000005,time:3831,execs:2280,op:havoc,rep:1)
         * UBSan: signed integer overflow: 4611686018427387893 * -4611686018427387893 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000005,time:3831,execs:2280,op:havoc,rep:1)
         */
        return n * ((l + r) / 2);
    }
}

int main(void) {
    int64_t l, r;
    printf("Enter the range l and r: ");
    if (scanf("%" SCNd64 " %" SCNd64, &l, &r) != 2) {
        printf("Invalid input\n");
        return 1;
    }

    int64_t result = sum_of_odd_numbers(l, r);
    printf("Sum of odd numbers in range [%" PRId64 ", %" PRId64 "] = %" PRId64 "\n", l, r, result);

    return 0;
}