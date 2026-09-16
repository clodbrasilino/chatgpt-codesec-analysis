#include <stdio.h>

double perimeter_of_rectangle(double length, double width) {
    return 2 * (length + width);
}

int main() {
    double length, width;
    printf("Enter the length of the rectangle: ");
    if (scanf("%lf", &length) != 1) {
        fprintf(stderr, "Error reading length\n");
        return 1;
    }
    printf("Enter the width of the rectangle: ");
    if (scanf("%lf", &width) != 1) {
        fprintf(stderr, "Error reading width\n");
        return 1;
    }

    double perimeter = perimeter_of_rectangle(length, width);
    printf("The perimeter of the rectangle is: %.2f\n", perimeter);
    return 0;
}