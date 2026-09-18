#include <stdio.h>
#include <stdlib.h>

double calculate_discriminant(double a, double b, double c){
    double discriminant = b * b - 4 * a * c;
    return discriminant;
}

int main() {
    double a, b, c, discriminant;

    printf("Enter coefficients a, b and c: ");
    if(scanf("%lf %lf %lf",&a, &b, &c) != 3){
       printf("Invalid input, please try again.");
       exit(EXIT_FAILURE);
    }

    discriminant = calculate_discriminant(a, b, c);

    if(discriminant < 0){
       printf("Discriminant is less than 0, roots are imaginary\n");
       exit(EXIT_FAILURE);
    }
    printf("Discriminant: %.2lf\n", discriminant);

    return 0;
}