#include <stdio.h>
#include <stdlib.h>

long long sum_of_squares_even(int n) {
    if (n < 0) {
        fprintf(stderr, "Error: n must be non-negative\n");
        exit(EXIT_FAILURE);
    }
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        long long even = 2LL * i;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223364155031292776 + 14522028965284 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:354,execs:204,op:havoc,rep:2)
         */
        sum += even * even;
    }
    return sum;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    long long result = sum_of_squares_even(n);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}