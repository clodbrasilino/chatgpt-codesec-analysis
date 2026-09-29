#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

unsigned long long permutation(int n, int k) {
    if (k > n || n < 0 || k < 0) {
        errno = EDOM;
        return 0;
    }
    
    unsigned long long result = 1;
    for (int i = 0; i < k; i++) {
        result *= (unsigned long long)(n - i);
    }
    return result;
}

int main(void) {
    int n, k;
    
    if (scanf("%d %d", &n, &k) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = permutation(n, k);
    
    if (errno == EDOM) {
        fprintf(stderr, "Invalid arguments: n must be >= k >= 0\n");
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}