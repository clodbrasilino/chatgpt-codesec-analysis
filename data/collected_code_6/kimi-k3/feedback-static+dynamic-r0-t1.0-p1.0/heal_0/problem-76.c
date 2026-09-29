#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long count_squares(long long m, long long n) {
    long long total = 0;
    long long min_dim = (m < n) ? m : n;
    
    for (long long k = 1; k <= min_dim; k++) {
        total += (m - k + 1) * (n - k + 1);
    }
    
    return total;
}

int main(void) {
    long long m, n;
    
    printf("Enter rectangle dimensions (m n): ");
    if (scanf("%lld %lld", &m, &n) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (m <= 0 || n <= 0) {
        fprintf(stderr, "Dimensions must be positive\n");
        return EXIT_FAILURE;
    }
    
    if (m > LLONG_MAX / n) {
        fprintf(stderr, "Input too large\n");
        return EXIT_FAILURE;
    }
    
    long long result = count_squares(m, n);
    printf("Number of squares: %lld\n", result);
    
    return EXIT_SUCCESS;
}