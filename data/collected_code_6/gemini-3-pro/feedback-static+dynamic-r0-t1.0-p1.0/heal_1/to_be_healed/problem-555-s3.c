#include <stdio.h>
#include <stdlib.h>

long long calculate_difference(int n) {
    if (n < 0) {
        return -1;
    }

    long long sum_n = (long long)n * (n + 1) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 555555561111111 * 555555561111111 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:96,execs:57,op:havoc,rep:1)
     */
    long long sum_cubes = sum_n * sum_n;

    return sum_cubes - sum_n;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }

    if (n < 0) {
        return EXIT_FAILURE;
    }

    long long result = calculate_difference(n);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}