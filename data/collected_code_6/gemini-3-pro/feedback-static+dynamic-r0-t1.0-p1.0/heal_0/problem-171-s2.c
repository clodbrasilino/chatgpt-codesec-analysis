#include <stdio.h>
#include <stdlib.h>

double calculate_pentagon_perimeter(double side1, double side2, double side3, double side4, double side5) {
    if (side1 <= 0.0 || side2 <= 0.0 || side3 <= 0.0 || side4 <= 0.0 || side5 <= 0.0) {
        return -1.0;
    }
    return side1 + side2 + side3 + side4 + side5;
}

int main(void) {
    double side1 = 0.0;
    double side2 = 0.0;
    double side3 = 0.0;
    double side4 = 0.0;
    double side5 = 0.0;
    double perimeter = 0.0;
    int result = 0;

    printf("Enter the lengths of the 5 sides of the pentagon separated by spaces:\n");
    result = scanf("%lf %lf %lf %lf %lf", &side1, &side2, &side3, &side4, &side5);

    if (result != 5) {
        fprintf(stderr, "Error: Invalid input format. Please enter 5 numeric values.\n");
        return EXIT_FAILURE;
    }

    perimeter = calculate_pentagon_perimeter(side1, side2, side3, side4, side5);

    if (perimeter < 0.0) {
        fprintf(stderr, "Error: Side lengths must be strictly positive numbers.\n");
        return EXIT_FAILURE;
    }

    printf("The perimeter of the pentagon is: %.2lf\n", perimeter);

    return EXIT_SUCCESS;
}