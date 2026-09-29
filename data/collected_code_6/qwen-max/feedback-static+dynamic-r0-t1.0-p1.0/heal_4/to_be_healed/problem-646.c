#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>

long long count_cubes(long n, long k) {
    if (n - k + 1 > LLONG_MAX / (n - k + 1)) {
        return 0;
    }
    long long result = (n - k + 1);
    long long temp_result = result * result;
    if (temp_result / result != result) {
        return 0;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 4937288444001 * 2222001 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000005,time:1580,execs:653,op:quick,pos:7)
     */
    long long final_result = temp_result * (n - k + 1);
    if (final_result / (n - k + 1) != temp_result) {
        return 0;
    }
    return final_result;
}

int main() {
    long n, k;
    if (scanf("%ld %ld", &n, &k) != 2 || n < k || k <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    printf("%lld\n", count_cubes(n, k));
    return EXIT_SUCCESS;
}