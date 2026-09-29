#include <stdio.h>
#include <math.h>

int check_quadratic_roots(double a, double b, double c) {
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return 0;
    }
    double sqrt_discriminant = sqrt(discriminant);
    double root1 = (-b + sqrt_discriminant) / (2 * a);
    double root2 = (-b - sqrt_discriminant) / (2 * a);
    return (root1 == 2 * root2) || (root2 == 2 * root1);
}

int main() {
    double a, b, c;
    printf("Enter coefficients a, b, and c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        return 1;
    }
    int result = check_quadratic_roots(a, b, c);
    if (result) {
        printf("One root of the quadratic equation is twice the other.\n");
    } else {
        printf("The roots do not satisfy the condition.\n");
    }
    return 0;
}