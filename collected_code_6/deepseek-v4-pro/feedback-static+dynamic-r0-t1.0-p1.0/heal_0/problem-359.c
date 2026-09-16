#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool isOneRootTwiceOther(double a, double b, double c) {
    if (fabs(a) < 1e-10) {
        return false;
    }
    
    double discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0) {
        return false;
    }
    
    if (fabs(discriminant) < 1e-10) {
        return false;
    }
    
    double root1 = (-b + sqrt(discriminant)) / (2 * a);
    double root2 = (-b - sqrt(discriminant)) / (2 * a);
    
    if (fabs(root2) < 1e-10) {
        return false;
    }
    
    double ratio1 = root1 / root2;
    double ratio2 = root2 / root1;
    
    if (fabs(ratio1 - 2.0) < 1e-10 || fabs(ratio1 - 0.5) < 1e-10 ||
        fabs(ratio2 - 2.0) < 1e-10 || fabs(ratio2 - 0.5) < 1e-10) {
        return true;
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
    
    if (isOneRootTwiceOther(a, b, c)) {
        printf("Yes, one root is twice the other\n");
    } else {
        printf("No, one root is not twice the other\n");
    }
    
    return 0;
}