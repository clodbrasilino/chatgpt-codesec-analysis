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

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 5 - -9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000008,time:25414,execs:17292,op:havoc,rep:3)
     */
    int64_t n = (r - l) / 2 + 1;

    if (n % 2 == 0) {
        return (n / 2) * ((uint64_t)l + (uint64_t)r);
    } else {
        if (l < 0 && r > 0) {
            return (n / 2) * ((uint64_t)l + (uint64_t)r) + (l + r) / 2;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2777777777777777777 * 2777777777777777779 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000008,time:25563,execs:17385,op:havoc,rep:5)
         * UBSan: signed integer overflow: 3888888888845 * 3888888888877 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000003,sig:06,src:000007,time:54299,execs:35753,op:havoc,rep:6)
         * UBSan: signed integer overflow: 4611685990649610127 * -4611685990649610127 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000005,time:10398,execs:7075,op:havoc,rep:2)
         * UBSan: signed integer overflow: 55555555555 + 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000005,time:10398,execs:7075,op:havoc,rep:2)
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