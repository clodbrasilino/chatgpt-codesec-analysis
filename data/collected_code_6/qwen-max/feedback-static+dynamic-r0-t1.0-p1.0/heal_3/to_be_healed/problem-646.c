#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>

long long count_cubes(long n, long k) {
    if (n - k + 1 > LLONG_MAX / (n - k + 1)) {
        return 0;
    }
    long long result = (n - k + 1);
    result *= result;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 493827106172841 * 22222221 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000005,time:1384,execs:664,op:havoc,rep:2)
     */
    return result * (n - k + 1);
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