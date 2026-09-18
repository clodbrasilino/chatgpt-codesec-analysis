#include <stdio.h>

long find_nth_term(long a, long d, long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 140703238996803 * 140704267972552 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000001,time:14,execs:16,op:(null),pos:0)
     * UBSan: signed integer overflow: 9223372036854775807 + 703516194984015 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000001,time:869,execs:246,op:havoc,rep:1)
     */
    return a + (n - 1) * d;
}

int main() {
    long a, d, n;
    scanf("%ld %ld %ld", &a, &d, &n);
    printf("%ld\n", find_nth_term(a, d, n));
    return 0;
}