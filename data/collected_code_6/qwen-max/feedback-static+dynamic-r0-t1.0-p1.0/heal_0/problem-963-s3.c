#include <stdio.h>

double calculate_discriminant(double a, double b, double c) {
    return b * b - 4 * a * c;
}

int main() {
    double a = 1.0;
    double b = 5.0;
    double c = 6.0;

    double discriminant = calculate_discriminant(a, b, c);

    printf("The discriminant is: %f\n", discriminant);

    return 0;
}