#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

long long sum_of_squares_odd(int n) {
    long long sum = 0;
    
    for (int i = 0; i < n; i++) {
        long long odd = 2LL * i + 1;
        long long square = odd * odd;
        
        if (square < 0 || sum > LLONG_MAX - square) {
            errno = ERANGE;
            return -1;
        }
        
        sum += square;
    }
    
    return sum;
}

int main(void) {
    int n;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    long long result = sum_of_squares_odd(n);
    
    if (errno == ERANGE) {
        fprintf(stderr, "Overflow detected: result too large to represent\n");
        return EXIT_FAILURE;
    }
    
    printf("Sum of squares of first %d odd natural numbers: %lld\n", n, result);
    
    return EXIT_SUCCESS;
}