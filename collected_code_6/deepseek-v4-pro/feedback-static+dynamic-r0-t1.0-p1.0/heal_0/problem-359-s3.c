#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool roots_are_in_ratio_two(double a, double b, double c) {
    if (fabs(a) < 1e-12) {
        return false;
    }
    
    double discriminant = b * b - 4.0 * a * c;
    
    if (discriminant < -1e-12) {
        return false;
    }
    
    if (fabs(discriminant) < 1e-12) {
        return false;
    }
    
    double sqrt_disc = sqrt(discriminant);
    double root1 = (-b + sqrt_disc) / (2.0 * a);
    double root2 = (-b - sqrt_disc) / (2.0 * a);
    
    if (fabs(root1) < 1e-12 && fabs(root2) < 1e-12) {
        return false;
    }
    
    if (fabs(root2) > 1e-12) {
        double ratio = root1 / root2;
        if (fabs(ratio - 2.0) < 1e-9 || fabs(ratio - 0.5) < 1e-9) {
            return true;
        }
    }
    
    if (fabs(root1) > 1e-12) {
        double ratio = root2 / root1;
        if (fabs(ratio - 2.0) < 1e-9 || fabs(ratio - 0.5) < 1e-9) {
            return true;
        }
    }
    
    return false;
}

int main(void) {
    double a, b, c;
    
    printf("Enter coefficients a, b, c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (roots_are_in_ratio_two(a, b, c)) {
        printf("One root is twice the other\n");
    } else {
        printf("Roots are not in the ratio 2:1\n");
    }
    
    return 0;
}