#include <stdio.h>

long long cubeSumOdd(int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        long long odd = 2LL * i + 1;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9222615723651324400 + 796108265857241 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:428,execs:440,op:havoc,rep:1)
         */
        sum += odd * odd * odd;
    }
    return sum;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n < 0) {
        return 1;
    }
    printf("%lld\n", cubeSumOdd(n));
    return 0;
}