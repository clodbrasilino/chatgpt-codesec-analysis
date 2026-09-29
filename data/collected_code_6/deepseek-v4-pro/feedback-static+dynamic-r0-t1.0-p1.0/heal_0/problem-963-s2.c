#include <stdio.h>
#include <stdlib.h>

double calculate_discriminant(double a, double b, double c) {
    if (a == 0) {
        fprintf(stderr, "Error: coefficient 'a' must be non-zero\n");
        exit(EXIT_FAILURE);
    }
    return b * b - 4 * a * c;
}

int main(void) {
    double a, b, c;
    double discriminant;

    printf("Enter coefficients a, b, c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    discriminant = calculate_discriminant(a, b, c);
    printf("Discriminant: %.2f\n", discriminant);

    return EXIT_SUCCESS;
}