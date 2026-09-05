#include <stdio.h>
#include <math.h>

int are_roots_reciprocal(double a, double b, double c) {
    if (a == 0.0) {
        return 0;
    }
    
    double discriminant = b * b - 4.0 * a * c;
    
    if (discriminant < 0.0) {
        return 0;
    }
    
    if (a == c) {
        if (discriminant == 0.0) {
            double root = -b / (2.0 * a);
            double abs_root = fabs(root);
            double epsilon = 1e-9;
            if (abs_root > epsilon && fabs(root - 1.0 / root) < epsilon) {
                return 1;
            }
            return 0;
        }
        return 1;
    }
    
    return 0;
}

int main(void) {
    double a, b, c;
    
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        return 1;
    }
    
    int result = are_roots_reciprocal(a, b, c);
    
    printf("%d\n", result);
    
    return 0;
}