#include <stdio.h>

long long sum_even_natural_numbers(long long l, long long r) {
    if (l > r) {
        return 0;
    }
    if (l <= 0) {
        l = 2;
    }
    if (r <= 0) {
        return 0;
    }
    if (l % 2 != 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:15030,execs:8590,op:havoc,rep:3)
         */
        l++;
    }
    if (l > r) {
        return 0;
    }
    if (r % 2 != 0) {
        r--;
    }
    if (l > r) {
        return 0;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775806 - -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:15030,execs:8590,op:havoc,rep:3)
     */
    long long n = ((r - l) / 2) + 1;
    if (l % 2 == 0 && n > 0 && l > (9223372036854775807LL - l) / n) {
        return -1;
    }
    if (n > 0 && l > 9223372036854775807LL / n) {
        return -1;
    }
    long long temp = n * l;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 - -1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:15030,execs:8590,op:havoc,rep:3)
     */
    if (temp > 9223372036854775807LL - (n - 1)) {
        return -1;
    }
    return temp + n - 1;
}

int main() {
    long long l, r;
    if (scanf("%lld %lld", &l, &r) != 2) {
        return 1;
    }
    long long result = sum_even_natural_numbers(l, r);
    printf("%lld\n", result);
    return 0;
}