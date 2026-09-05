#include <stdio.h>

double trapezium_area(double base1, double base2, double height)
{
    if (base1 < 0.0 || base2 < 0.0 || height < 0.0) {
        return -1.0;
    }
    return 0.5 * (base1 + base2) * height;
}

int main(void)
{
    double base1, base2, height, area;

    printf("Enter the length of the first base: ");
    if (scanf("%lf", &base1) != 1) {
        fprintf(stderr, "Invalid input for first base\n");
        return 1;
    }

    printf("Enter the length of the second base: ");
    if (scanf("%lf", &base2) != 1) {
        fprintf(stderr, "Invalid input for second base\n");
        return 1;
    }

    printf("Enter the height: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Invalid input for height\n");
        return 1;
    }

    area = trapezium_area(base1, base2, height);

    if (area < 0.0) {
        fprintf(stderr, "Invalid dimensions: values must be non-negative\n");
        return 1;
    }

    printf("Area of trapezium: %.2f\n", area);

    return 0;
}