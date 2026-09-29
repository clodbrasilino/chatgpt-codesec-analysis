#include <stdio.h>
#include <math.h>

int checkOppositeRoots(double a, double b, double c) {
    if (a == 0.0) {
        return 0;
    }
    
    double discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0) {
        return 0;
    }
    
    double sum = -b / a;
    double product = c / a;
    
    return (sum == 0.0 && product <= 0.0);
}

int main(void) {
    double a, b, c;
    
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        return 1;
    }
    
    if (checkOppositeRoots(a, b, c)) {
        printf("Roots are numerically equal but opposite in sign\n");
    } else {
        printf("Roots are not numerically equal but opposite in sign\n");
    }
    
    return 0;
}