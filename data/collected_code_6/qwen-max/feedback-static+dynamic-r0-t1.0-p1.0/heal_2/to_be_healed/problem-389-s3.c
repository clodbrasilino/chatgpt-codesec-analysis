#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

long long lucas_number(int n) {
    if (n == 0) return 2;
    if (n == 1) return 1;

    long long a = 2, b = 1;
    for (int i = 2; i <= n; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 3980154972736918051 + 6440026026380244498 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:154,execs:150,op:havoc,rep:4)
         */
        long long c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n;
    printf("Enter the index of the Lucas number: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Index must be non-negative\n");
        return EXIT_FAILURE;
    }

    long long result = lucas_number(n);
    printf("The %dth Lucas number is: %lld\n", n, result);
    return EXIT_SUCCESS;
}