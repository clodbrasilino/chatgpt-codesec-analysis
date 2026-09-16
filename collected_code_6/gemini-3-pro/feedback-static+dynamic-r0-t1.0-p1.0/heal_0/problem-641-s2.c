#include <stdio.h>
#include <stdlib.h>

unsigned long long int findNonagonalNumber(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    return (unsigned long long int)n * (7ULL * n - 5ULL) / 2ULL;
}

int main(void) {
    unsigned int n;
    
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long int result = findNonagonalNumber(n);
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}