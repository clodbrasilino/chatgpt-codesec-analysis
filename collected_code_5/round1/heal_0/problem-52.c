#include <stdio.h>

double calculateArea(double base, double height) {
    if (base <= 0 || height <= 0) {
        printf("Error: Base and height must be positive numbers\n");
        return -1;
    }

    return base * height;
}

int main(void) {
    double base, height, area;

    printf("Enter the base of the parallelogram: ");
    if (scanf("%lf", &base) != 1 ) {
        printf("Error: Invalid input\n");
        return 1;
    }

    printf("Enter the height of the parallelogram: ");
    if (scanf("%lf", &height) != 1) {
        printf("Error: Invalid input\n");
        return 1;
    }

    area = calculateArea(base, height);
    if (area > 0) {
        printf("The area of the parallelogram is: %.2lf\n", area);
    }

    return 0;
}