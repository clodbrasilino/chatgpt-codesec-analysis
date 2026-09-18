#include <stdio.h>
#include <stdlib.h>

long long find_arithmetic_term(int n, long long a, long long d) {
    if (n <= 0) {
        exit(EXIT_FAILURE);
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 111111 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:7379,execs:4513,op:havoc,rep:6)
     * UBSan: signed integer overflow: 6 + 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:2756,execs:1766,op:havoc,rep:2)
     */
    return a + (long long)(n - 1) * d;
}

int main(void) {
    int n;
    long long a, d, term;

    if (scanf("%d %lld %lld", &n, &a, &d) != 3) {
        return EXIT_FAILURE;
    }

    term = find_arithmetic_term(n, a, d);

    printf("%lld\n", term);

    return EXIT_SUCCESS;
}