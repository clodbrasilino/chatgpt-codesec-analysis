#include <stdio.h>
#include <math.h>
#include <float.h>

double calculate_geometric_sum(double r, int n);

double calculate_geometric_sum(double r, int n) {
    if (n <= 0) {
        return 0.0;
    }
    if (fabs(r - 1.0) < DBL_EPSILON) {
        return (double)n;
    }
    return (1.0 - pow(r, n)) / (1.0 - r);
}

int main(void) {
    double r = 2.0;
    int n = 5;
    double result = 0.0;

    result = calculate_geometric_sum(r, n);
    
    if (printf("%.6f\n", result) < 0) {
        return 1;
    }

    return 0;
}