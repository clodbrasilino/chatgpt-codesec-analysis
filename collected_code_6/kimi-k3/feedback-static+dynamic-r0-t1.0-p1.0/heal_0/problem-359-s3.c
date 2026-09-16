#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool is_root_twice_other(double a, double b, double c) {
    if (a == 0.0) {
        return false;
    }
    
    double discriminant = b * b - 4.0 * a * c;
    
    if (discriminant < 0.0) {
        return false;
    }
    
    double sqrt_d = sqrt(discriminant);
    double root1 = (-b + sqrt_d) / (2.0 * a);
    double root2 = (-b - sqrt_d) / (2.0 * a);
    
    const double epsilon = 1e-9;
    
    bool condition1 = fabs(root1 - 2.0 * root2) < epsilon;
    bool condition2 = fabs(root2 - 2.0 * root1) < epsilon;
    
    return condition1 || condition2;
}

int main(void) {
    double a, b, c;
    
    printf("Enter coefficients a, b, c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (is_root_twice_other(a, b, c)) {
        printf("One root is twice the other\n");
    } else {
        printf("One root is not twice the other\n");
    }
    
    return 0;
}