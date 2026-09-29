#include <stdio.h>
#include <stdlib.h>

long long sum_of_ap(long long n, long long a, long long d) {
    if (n <= 0) {
        return 0;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 * 6 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:342,execs:189,op:havoc,rep:1)
     * UBSan: signed integer overflow: 9223372036854775806 * 2 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:342,execs:189,op:havoc,rep:1)
     * UBSan: signed integer overflow: 111111111111111 * 666666666666664 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:252,execs:144,op:havoc,rep:2)
     * UBSan: signed integer overflow: 2 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:751,execs:402,op:havoc,rep:2)
     */
    return (n * ((2 * a) + ((n - 1) * d))) / 2;
}

int main(void) {
    long long n;
    long long a;
    long long d;
    long long sum;

    if (scanf("%lld %lld %lld", &n, &a, &d) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Number of terms cannot be negative\n");
        return EXIT_FAILURE;
    }

    sum = sum_of_ap(n, a, d);

    printf("%lld\n", sum);

    return EXIT_SUCCESS;
}