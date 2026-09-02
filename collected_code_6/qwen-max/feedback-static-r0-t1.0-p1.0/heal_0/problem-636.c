#include <stdio.h>
#include <math.h>

int are_roots_reciprocal(double a, double b, double c) {
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return 0;
    }
    double root1 = (-b + sqrt(discriminant)) / (2 * a);
    double root2 = (-b - sqrt(discriminant)) / (2 * a);
    return fabs(root1 * root2 - 1.0) < 1e-9;
}

int main() {
    double a, b, c;
    printf("Enter coefficients a, b, and c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3 || a == 0.0) {
        printf("Invalid input or not a quadratic equation.\n");
        return 1;
    }
    if (are_roots_reciprocal(a, b, c)) {
        printf("The roots are reciprocal of each other.\n");
    } else {
        printf("The roots are not reciprocal of each other.\n");
    }
    return 0;
}