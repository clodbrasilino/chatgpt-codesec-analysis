#include <stdio.h>
#include <stdlib.h>

long long findStarNumber(int n) {
    if (n <= 0) {
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9476330832 * 1579388471 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:711,execs:356,op:quick,pos:19)
     */
    return 6LL * n * (n - 1) + 1;
}

int main() {
    int n;
    long long starNumber;

    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    starNumber = findStarNumber(n);

    if (starNumber == -1) {
        fprintf(stderr, "Input must be a positive integer\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", starNumber);

    return EXIT_SUCCESS;
}