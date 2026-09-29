#include <stdio.h>
#include <math.h>

double calculate_discriminant(double a, double b, double c) {
    return b * b - 4 * a * c;
}

int main() {
    double a, b, c, discriminant;

    printf("Enter coefficients a, b and c: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    discriminant = calculate_discriminant(a, b, c);

    printf("Discriminant: %.2lf\n", discriminant);

    return 0;
}