#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

double geometric_sum(int n, double ratio)
{
    if (n <= 0) {
        return 0.0;
    }
    
    if (ratio == 1.0) {
        return (double)(n - 1);
    }
    
    double term = 1.0;
    double sum = 0.0;
    int i;
    
    for (i = 0; i < n - 1; i++) {
        sum += term;
        term *= ratio;
    }
    
    return sum;
}

int main(void)
{
    int n;
    double ratio;
    double result;
    
    printf("Enter n (number of terms): ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input for n\n");
        return EXIT_FAILURE;
    }
    
    if (n <= 0) {
        fprintf(stderr, "n must be positive\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter ratio: ");
    if (scanf("%lf", &ratio) != 1) {
        fprintf(stderr, "Invalid input for ratio\n");
        return EXIT_FAILURE;
    }
    
    result = geometric_sum(n, ratio);
    
    printf("Geometric sum of %d terms: %f\n", n - 1, result);
    
    return EXIT_SUCCESS;
}