#include <stdio.h>
#include <math.h>

int isOneRootTwiceOther(double a, double b, double c) {
    if (a == 0.0) {
        return 0;
    }
    
    double discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0) {
        return 0;
    }
    
    double sqrt_discriminant = sqrt(discriminant);
    double root1 = (-b + sqrt_discriminant) / (2.0 * a);
    double root2 = (-b - sqrt_discriminant) / (2.0 * a);
    
    double epsilon = 1e-9;
    if (fabs(root1 - 2.0 * root2) < epsilon || fabs(root2 - 2.0 * root1) < epsilon) {
        return 1;
    }
    
    return 0;
}

int main(void) {
    double a, b, c;
    
    printf("Enter coefficients a, b, and c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (isOneRootTwiceOther(a, b, c)) {
        printf("One root is twice the other\n");
    } else {
        printf("One root is not twice the other\n");
    }
    
    return 0;
}