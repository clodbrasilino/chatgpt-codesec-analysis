#include <stdio.h>
#include <math.h>

double calculate_discriminant(double a, double b, double c) {
    if (a == 0.0) {
        fprintf(stderr, "Error: 'a' cannot be zero.\n");
        return NAN;
    }
    return b * b - 4 * a * c;
}

int main(void) {
    double a, b, c;

    printf("Enter coefficients a, b, and c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Error: Invalid input.\n");
        return 1;
    }

    double discriminant = calculate_discriminant(a, b, c);
    if (!isnan(discriminant)) {
        printf("Discriminant: %.2f\n", discriminant);
    }

    return 0;
}