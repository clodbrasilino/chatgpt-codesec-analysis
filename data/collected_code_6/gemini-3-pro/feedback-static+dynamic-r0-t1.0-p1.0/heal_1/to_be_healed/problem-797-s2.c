#include <stdio.h>
#include <stdlib.h>

long long sum_odd_numbers(long long l, long long r) {
    if (l > r || l < 0) {
        return -1;
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

    long long n = ((r - l) / 2) + 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 66667 + 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000006,time:4230,execs:1738,op:havoc,rep:4)
     * UBSan: signed integer overflow: 3333333000000 * 6666667333244 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:1827,execs:928,op:havoc,rep:6)
     * UBSan: signed integer overflow: 4611686018427354571 * -9223372036854709142 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000006,time:4230,execs:1738,op:havoc,rep:4)
     */
    return n * (l + r) / 2;
}

int main() {
    long long l, r;
    long long sum;

    if (scanf("%lld %lld", &l, &r) != 2) {
        return EXIT_FAILURE;
    }

    sum = sum_odd_numbers(l, r);

    if (sum == -1) {
        return EXIT_FAILURE;
    }

    printf("%lld\n", sum);

    return EXIT_SUCCESS;
}