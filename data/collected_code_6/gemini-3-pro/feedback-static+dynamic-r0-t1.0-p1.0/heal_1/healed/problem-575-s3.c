#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long findNthNotMultiple(long long n, long long k) {
    if (k <= 1 || n < 1) {
        return -1; 
    }
    long long q = n / (k - 1);
    long long r = n % (k - 1);
    
    unsigned long long uq = (unsigned long long)q;
    unsigned long long uk = (unsigned long long)k;
    unsigned long long ur = (unsigned long long)r;
    
    unsigned long long result_u;
    
    if (r == 0) {
        result_u = uq * uk - 1;
    } else {
        result_u = uq * uk + ur;
    }
    
    if (result_u > (unsigned long long)LLONG_MAX) {
        return -1; 
    }
    
    return (long long)result_u;
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