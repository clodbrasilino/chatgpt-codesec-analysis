#include <stdio.h>

double calculate_perimeter(double a, double b, double c) {
    return a + b + c;
}

int main() {
    double side1, side2, side3;
    printf("Enter the sides of the triangle: ");
    if (scanf("%lf %lf %lf", &side1, &side2, &side3) != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (side1 <= 0 || side2 <= 0 || side3 <= 0) {
        fprintf(stderr, "Sides must be positive numbers\n");
        return 1;
    }
    if (side1 + side2 <= side3 || side1 + side3 <= side2 || side2 + side3 <= side1) {
        fprintf(stderr, "Invalid triangle sides\n");
        return 1;
    }
    double perimeter = calculate_perimeter(side1, side2, side3);
    printf("The perimeter is: %.2f\n", perimeter);
    return 0;
}