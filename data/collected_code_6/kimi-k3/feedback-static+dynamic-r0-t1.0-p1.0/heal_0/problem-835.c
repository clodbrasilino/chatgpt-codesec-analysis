#include <stdio.h>
#include <math.h>

int calculate_slope(double x1, double y1, double x2, double y2, double *slope)
{
    double denominator;
    
    if (slope == NULL) {
        return -1;
    }
    
    denominator = x2 - x1;
    
    if (fabs(denominator) < 1e-9) {
        return -1;
    }
    
    *slope = (y2 - y1) / denominator;
    return 0;
}

int main(void)
{
    double x1, y1, x2, y2;
    double slope;
    int result;
    
    printf("Enter coordinates of first point (x1 y1): ");
    if (scanf("%lf %lf", &x1, &y1) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("Enter coordinates of second point (x2 y2): ");
    if (scanf("%lf %lf", &x2, &y2) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    result = calculate_slope(x1, y1, x2, y2, &slope);
    
    if (result != 0) {
        fprintf(stderr, "Cannot calculate slope: vertical line or invalid parameters\n");
        return 1;
    }
    
    printf("Slope: %.6f\n", slope);
    
    return 0;
}