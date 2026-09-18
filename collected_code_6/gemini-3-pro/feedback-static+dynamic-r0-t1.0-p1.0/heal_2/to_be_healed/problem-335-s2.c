#include <stdio.h>
#include <stdlib.h>

long long sum_of_ap(long long n, long long a, long long d) {
    if (n <= 0) {
        return 0;
    }
    __int128 n_128 = n;
    __int128 a_128 = a;
    __int128 d_128 = d;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 * 0x00000000000000010000000000000006 cannot be represented in type '__int128' (AFL crash: id:000000,sig:06,src:000001,time:1203,execs:148,op:havoc,rep:1)
     */
    __int128 sum = (n_128 * ((2 * a_128) + ((n_128 - 1) * d_128))) / 2;
    return (long long)sum;
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