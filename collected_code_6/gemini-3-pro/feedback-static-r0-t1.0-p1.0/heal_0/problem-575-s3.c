#include <stdio.h>
#include <stdlib.h>

long long findNthNotMultiple(long long n, long long k) {
    if (k <= 1 || n < 1) {
        return -1; 
    }
    long long q = n / (k - 1);
    long long r = n % (k - 1);
    
    if (r == 0) {
        return q * k - 1;
    } else {
        return q * k + r;
    }
}

int main(void) {
    long long n = 0;
    long long k = 0;

    if (scanf("%lld %lld", &n, &k) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    long long result = findNthNotMultiple(n, k);
    if (result == -1) {
        fprintf(stderr, "Invalid parameters.\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}