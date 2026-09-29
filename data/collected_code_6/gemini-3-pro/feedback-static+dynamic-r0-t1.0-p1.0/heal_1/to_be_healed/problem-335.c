#include <stdio.h>
#include <stdlib.h>

long long sum_of_arithmetic_progression(long long a, long long d, long long n) {
    if (n < 0) {
        return 0;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 + 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:6585,execs:3576,op:havoc,rep:1)
     * UBSan: signed integer overflow: 2 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:2191,execs:1232,op:havoc,rep:2)
     * UBSan: signed integer overflow: 55555555555 * 333333333326 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000001,time:8523,execs:4618,op:havoc,rep:22)
     * UBSan: signed integer overflow: 9223372036854775806 * 6 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:8273,execs:4485,op:havoc,rep:3)
     * UBSan: signed integer overflow: 2 * -9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:6585,execs:3576,op:havoc,rep:1)
     * UBSan: signed integer overflow: 9223372036854775807 * -10 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:8273,execs:4485,op:havoc,rep:3)
     */
    return (n * ((2 * a) + (n - 1) * d)) / 2;
}

int main(void) {
    long long a = 0;
    long long d = 0;
    long long n = 0;
    long long sum = 0;
    int result = 0;

    result = scanf("%lld %lld %lld", &a, &d, &n);
    if (result != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Number of terms cannot be negative\n");
        return EXIT_FAILURE;
    }

    sum = sum_of_arithmetic_progression(a, d, n);
    
    printf("%lld\n", sum);

    return EXIT_SUCCESS;
}