#include <stdio.h>

double calculate_perimeter(double a, double b, double c) {
    return a + b + c;
}

int main() {
    double side_a, side_b, side_c;
    printf("Enter the lengths of the sides of the triangle: ");
    if (scanf("%lf %lf %lf", &side_a, &side_b, &side_c) != 3) {
        printf("Invalid input.\n");
        return 1;
    }
    double perimeter = calculate_perimeter(side_a, side_b, side_c);
    printf("The perimeter of the triangle is: %.2f\n", perimeter);
    return 0;
}