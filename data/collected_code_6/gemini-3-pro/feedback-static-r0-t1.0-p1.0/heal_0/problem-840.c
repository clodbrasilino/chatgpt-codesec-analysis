#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool checkRootsEqualAndOpposite(double a, double b, double c) {
    if (a == 0) {
        return false;
    }
    
    double discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0) {
        return false;
    }
    
    double root1 = (-b + sqrt(discriminant)) / (2 * a);
    double root2 = (-b - sqrt(discriminant)) / (2 * a);
    
    if (fabs(root1 + root2) < 1e-9 && fabs(root1) > 1e-9) {
        return true;
    }
    
    return false;
}

int main() {
    double a = 1.0;
    double b = 0.0;
    double c = -4.0;
    
    if (checkRootsEqualAndOpposite(a, b, c)) {
        printf("Roots are numerically equal but opposite in sign.\n");
    } else {
        printf("Roots are not numerically equal but opposite in sign.\n");
    }
    
    return 0;
}