#include <stdio.h>

double calculate_parallelogram_area(double base, double height) {
    if (base < 0 || height < 0) {
        return -1;
    }
    return base * height;
}

int main(void) {
    double base, height, area;

    printf("Enter base: ");
    if (scanf("%lf", &base) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("Enter height: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    area = calculate_parallelogram_area(base, height);

    if (area < 0) {
        fprintf(stderr, "Base and height must be non-negative\n");
        return 1;
    }

    printf("Area: %.2f\n", area);
    return 0;
}