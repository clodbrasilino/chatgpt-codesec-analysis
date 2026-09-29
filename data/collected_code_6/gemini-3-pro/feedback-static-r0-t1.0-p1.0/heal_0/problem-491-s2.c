#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double sum_geometric_progression(double a, double r, int n) {
    if (n <= 0) {
        return 0.0;
    }
    
    if (fabs(r - 1.0) < 1e-9) {
        return a * n;
    }
    
    return a * (1.0 - pow(r, n)) / (1.0 - r);
}

int main(void) {
    double a = 0.0;
    double r = 0.0;
    int n = 0;
    
    if (scanf("%lf %lf %d", &a, &r, &n) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Number of terms cannot be negative\n");
        return EXIT_FAILURE;
    }
    
    double sum = sum_geometric_progression(a, r, n);
    printf("%.6f\n", sum);
    
    return EXIT_SUCCESS;
}