#include <stdio.h>

double square_perimeter(double side) {
    return 4.0 * side;
}

int main(void) {
    double side = 0.0;
    double perimeter = 0.0;

    printf("Enter the side length of the square: ");
    if (scanf("%lf", &side) != 1) {
        fprintf(stderr, "Invalid input. Please enter a numeric value.\n");
        return 1;
    }

    if (side < 0) {
        fprintf(stderr, "Side length cannot be negative.\n");
        return 1;
    }

    perimeter = square_perimeter(side);

    printf("Perimeter of the square: %.2f\n", perimeter);

    return 0;
}