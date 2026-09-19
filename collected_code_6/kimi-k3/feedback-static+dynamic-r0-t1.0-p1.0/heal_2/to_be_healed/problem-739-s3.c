#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

long find_smallest_triangular_index(int n) {
    if (n <= 0) {
        return -1;
    }
    
    double lower_bound = pow(10.0, n - 1);
    double discriminant = 2.0 * lower_bound - 2.0;
    
    if (discriminant < 0.0) {
        return -1;
    }
    
    errno = 0;
    /* Possible weaknesses found:
     *  Variable 'sqrt_val' is assigned a value that is never used. [unreadVariable]
     *  Value stored to 'sqrt_val' during its initialization is never read [deadcode.DeadStores]
     */
    double sqrt_val = sqrt(discriminant);
    if (errno == EDOM) {
        return -1;
    }
    
    double k = (-1.0 + sqrt(1.0 + 8.0 * lower_bound)) / 2.0;
    
    if (!isfinite(k) || k < 0.0 || k >= (double)LONG_MAX) {
        return -1;
    }
    
    double ceil_k = ceil(k);
    if (!isfinite(ceil_k) || ceil_k >= (double)LONG_MAX) {
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