#include <stdio.h>
#include <math.h>

int areRootsReciprocal(double a, double b, double c) {
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return 0;

    double root1 = (-b + sqrt(discriminant)) / (2 * a);
    double root2 = (-b - sqrt(discriminant)) / (2 * a);

    return (root1 != 0 && root2 != 0 && root1 == 1.0 / root2);
}

int main() {
    double a, b, c;

    printf("Enter coefficients a, b, and c: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    if (areRootsReciprocal(a, b, c)) {
        printf("The roots are reciprocal of each other.\n");
    } else {
        printf("The roots are not reciprocal of each other.\n");
    }

    return 0;
}