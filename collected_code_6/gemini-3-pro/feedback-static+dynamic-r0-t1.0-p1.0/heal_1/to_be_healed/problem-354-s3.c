#include <stdio.h>
#include <stdlib.h>

long long int find_nth_term(long long int a, long long int d, long long int n) {
    if (n <= 0) {
        return 0;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 11 + 9223372036854775798 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:1532,execs:851,op:havoc,rep:5)
     * UBSan: signed integer overflow: 9223372036854775806 * 5 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:1532,execs:851,op:havoc,rep:5)
     * UBSan: signed integer overflow: 9223372036854775807 + 49999999999990 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:2645,execs:1368,op:havoc,rep:4)
     */
    return a + (n - 1) * d;
}

int main(void) {
    long long int a = 0;
    long long int d = 0;
    long long int n = 0;
    long long int result = 0;

    if (scanf("%lld %lld %lld", &a, &d, &n) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n <= 0) {
        fprintf(stderr, "n must be greater than 0\n");
        return EXIT_FAILURE;
    }

    result = find_nth_term(a, d, n);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}