#include <stdio.h>
#include <stdlib.h>

long long count_cubes(int n, int k) {
    if (n < k || k <= 0) {
        return 0;
    }
    long long diff = (long long)n - k;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 109781424355840000 * 331332800 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000005,time:1590,execs:776,op:havoc,rep:4)
     */
    return diff * diff * diff;
}

int main(void) {
    int n, k;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    printf("Enter k: ");
    if (scanf("%d", &k) != 1) {
        return EXIT_FAILURE;
    }
    if (n < 0 || k <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    printf("%lld\n", count_cubes(n, k));
    return EXIT_SUCCESS;
}