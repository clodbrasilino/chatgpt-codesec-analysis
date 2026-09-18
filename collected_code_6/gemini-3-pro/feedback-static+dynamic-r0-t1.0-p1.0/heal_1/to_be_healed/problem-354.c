#include <stdio.h>
#include <stdlib.h>

long long find_nth_term(long long a, long long d, long long n) {
    if (n <= 0) {
        return 0;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 + 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:1501,execs:757,op:havoc,rep:3)
     * UBSan: signed integer overflow: 6666666676666666659 * 66666 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:7829,execs:3918,op:havoc,rep:13)
     */
    return a + (n - 1) * d;
}

int main(void) {
    long long a = 0;
    long long d = 0;
    long long n = 0;

    if (scanf("%lld %lld %lld", &a, &d, &n) != 3) {
        return EXIT_FAILURE;
    }

    if (n <= 0) {
        return EXIT_FAILURE;
    }

    long long result = find_nth_term(a, d, n);

    if (printf("%lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}