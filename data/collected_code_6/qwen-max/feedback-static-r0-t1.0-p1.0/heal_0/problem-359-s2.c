#include <stdio.h>
#include <math.h>

int is_one_root_double_of_other(double a, double b, double c) {
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return 0;
    }
    double root1 = (-b + sqrt(discriminant)) / (2 * a);
    double root2 = (-b - sqrt(discriminant)) / (2 * a);
    if (root1 == 2 * root2 || root2 == 2 * root1) {
        return 1;
    }
    return 0;
}

int main() {
    double a, b, c;
    printf("Enter coefficients a, b, c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3 || a == 0.0) {
        fprintf(stderr, "Invalid input or the equation is not quadratic.\n");
        return 1;
    }
    if (is_one_root_double_of_other(a, b, c)) {
        printf("One root is twice of the other.\n");
    } else {
        printf("Neither root is twice of the other.\n");
    }
    return 0;
}