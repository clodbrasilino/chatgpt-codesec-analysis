#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

long find_smallest_triangular_index(int n) {
    if (n <= 0) {
        return -1;
    }
    
    if (n > 18) {
        return -1;
    }
    
    double lower_bound = pow(10.0, n - 1);
    double discriminant = 1.0 + 8.0 * lower_bound;
    
    if (isinf(discriminant) || isnan(discriminant)) {
        return -1;
    }
    
    double k = (-1.0 + sqrt(discriminant)) / 2.0;
    
    if (isinf(k) || isnan(k)) {
        return -1;
    }
    
    double ceil_k = ceil(k);
    
    if (isinf(ceil_k) || isnan(ceil_k)) {
        return -1;
    }
    
    if (ceil_k > (double)LONG_MAX || ceil_k < (double)LONG_MIN) {
        return -1;
    }
    
    long index = (long)ceil_k;
    
    if (index < 0) {
        return -1;
    }
    
    return index;
}

int main(void) {
    int n;
    
    printf("Enter number of digits: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n <= 0) {
        fprintf(stderr, "Number of digits must be positive\n");
        return EXIT_FAILURE;
    }
    
    long result = find_smallest_triangular_index(n);
    
    if (result == -1) {
        fprintf(stderr, "Error calculating triangular number\n");
        return EXIT_FAILURE;
    }
    
    printf("Index of smallest triangular number with %d digits: %ld\n", n, result);
    
    return EXIT_SUCCESS;
}