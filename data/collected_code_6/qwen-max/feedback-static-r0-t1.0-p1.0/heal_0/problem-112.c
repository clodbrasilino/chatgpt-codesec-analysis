#include <stdio.h>

double calculate_perimeter(double radius, double height) {
    if (radius > 0 && height > 0) {
        return 2 * (3.14159 * radius + height);
    }
    return -1;
}

int main() {
    double radius, height;
    printf("Enter the radius and height of the cylinder: ");
    int res = scanf("%lf %lf", &radius, &height);
    if (res == 2) {
        double perimeter = calculate_perimeter(radius, height);
        if (perimeter >= 0) {
            printf("The perimeter of the cylinder is: %.2f\n", perimeter);
        } else {
            printf("Invalid input. Radius and height must be positive numbers.\n");
        }
    } else {
        printf("Invalid input. Please enter valid numbers for radius and height.\n");
    }
    return 0;
}