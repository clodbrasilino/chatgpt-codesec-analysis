#include <stdio.h>

long long square_sum(long long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -2835209191934047940 * -2835209191934047940 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:1590,execs:693,op:havoc,rep:4)
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:273,execs:131,op:havoc,rep:2)
     * UBSan: signed integer overflow: 733395532716 * 733395532716 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:315,execs:150,op:havoc,rep:4)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:273,execs:131,op:havoc,rep:2)
     * UBSan: signed integer overflow: -4611686018427387904 * -4611686018427387904 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:273,execs:131,op:havoc,rep:2)
     * UBSan: signed integer overflow: 11111111111 * 11111111112 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:1590,execs:693,op:havoc,rep:4)
     */
    return (n * (n + 1) / 2) * (n * (n + 1) / 2);
}

long long sum_of_squares(long long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -9223372036854775808 * -1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:273,execs:131,op:havoc,rep:2)
     * UBSan: signed integer overflow: 2 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:273,execs:131,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:273,execs:131,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:273,execs:131,op:havoc,rep:2)
     * UBSan: signed integer overflow: -5670418383868095880 * 22222222223 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:1590,execs:693,op:havoc,rep:4)
     * UBSan: signed integer overflow: 11111111111 * 11111111112 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:1590,execs:693,op:havoc,rep:4)
     */
    return n * (n + 1) * (2 * n + 1) / 6;
}

long long difference_between_sums(long long n) {
    return square_sum(n) - sum_of_squares(n);
}

int main() {
    long long n;
    printf("Enter a number: ");
    if (scanf("%lld", &n) != 1) {
        return 1;
    }
    printf("Difference: %lld\n", difference_between_sums(n));
    return 0;
}