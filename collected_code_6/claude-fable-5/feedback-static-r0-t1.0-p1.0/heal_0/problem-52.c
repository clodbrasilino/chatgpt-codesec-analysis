#include <stdio.h>
#include <stdlib.h>

double parallelogram_area(double base, double height);

double parallelogram_area(double base, double height)
{
    return base * height;
}

int main(void)
{
    double base = 0.0;
    double height = 0.0;
    double area = 0.0;

    printf("Enter base: ");
    if (scanf("%lf", &base) != 1) {
        fprintf(stderr, "Error: invalid input for base.\n");
        return EXIT_FAILURE;
    }

    printf("Enter height: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Error: invalid input for height.\n");
        return EXIT_FAILURE;
    }

    if (base <= 0.0 || height <= 0.0) {
        fprintf(stderr, "Error: base and height must be positive values.\n");
        return EXIT_FAILURE;
    }

    area = parallelogram_area(base, height);

    if (printf("Area of parallelogram: %.2f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}