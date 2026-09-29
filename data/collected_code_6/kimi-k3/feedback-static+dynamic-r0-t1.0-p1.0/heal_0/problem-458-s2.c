#include <stdio.h>

double calculate_rectangle_area(double length, double width);

int main(void) {
    double length = 0.0;
    double width = 0.0;
    double area = 0.0;

    printf("Enter length: ");
    if (scanf("%lf", &length) != 1) {
        fprintf(stderr, "Invalid input for length\n");
        return 1;
    }

    printf("Enter width: ");
    if (scanf("%lf", &width) != 1) {
        fprintf(stderr, "Invalid input for width\n");
        return 1;
    }

    if (length < 0.0 || width < 0.0) {
        fprintf(stderr, "Dimensions cannot be negative\n");
        return 1;
    }

    area = calculate_rectangle_area(length, width);
    printf("Area: %.2f\n", area);

    return 0;
}

double calculate_rectangle_area(double length, double width) {
    return length * width;
}