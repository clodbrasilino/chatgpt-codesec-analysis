#include <stdio.h>
#include <math.h>

int check_roots(double a, double b, double c) {
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return 0;
    }
    double root1 = (-b + sqrt(discriminant)) / (2 * a);
    double root2 = (-b - sqrt(discriminant)) / (2 * a);
    return (root1 == -root2);
}

int main() {
    double a, b, c;
    printf("Enter coefficients a, b, c: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    if (a == 0) {
        printf("Not a quadratic equation.\n");
    } else {
        int result = check_roots(a, b, c);
        if (result) {
            printf("The roots are numerically equal but opposite in sign.\n");
        } else {
            printf("The roots are not numerically equal but opposite in sign.\n");
        }
    }

    return 0;
}