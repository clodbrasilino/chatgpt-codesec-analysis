#include <stdio.h>
#include <math.h>

int isValidTriangle(double angle1, double angle2, double angle3) {
    const double epsilon = 1e-9;
    const double sum = angle1 + angle2 + angle3;
    
    if (angle1 <= 0.0 || angle2 <= 0.0 || angle3 <= 0.0) {
        return 0;
    }
    
    if (fabs(sum - 180.0) > epsilon) {
        return 0;
    }
    
    return 1;
}

int main(void) {
    double a, b, c;
    
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (isValidTriangle(a, b, c)) {
        printf("Valid triangle\n");
    } else {
        printf("Invalid triangle\n");
    }
    
    return 0;
}