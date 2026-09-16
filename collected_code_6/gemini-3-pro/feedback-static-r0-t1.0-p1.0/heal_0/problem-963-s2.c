#include <stdio.h>

double calculate_discriminant(double a, double b, double c) {
    return (b * b) - (4 * a * c);
}

int main(void) {
    double a, b, c, discriminant;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Error: Invalid input.\n");
        return 1;
    }

    discriminant = calculate_discriminant(a, b, c);
    printf("%lf\n", discriminant);

    return 0;
}