#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-10

int validate_dimensions(double a, double b, double c, double h) {
    if (a <= 0 || b <= 0 || c <= 0 || h <= 0) {
        return 0;
    }
    if (a + b <= c || a + c <= b || b + c <= a) {
        return 0;
    }
    return 1;
}

double triangle_area(double a, double b, double c) {
    double s = (a + b + c) / 2.0;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

double triangular_prism_volume(double a, double b, double c, double h) {
    double area;
    if (!validate_dimensions(a, b, c, h)) {
        return -1.0;
    }
    area = triangle_area(a, b, c);
    if (area < EPSILON) {
        return -1.0;
    }
    return area * h;
}

int main(void) {
    double a, b, c, h, volume;
    int result;

    printf("Enter the three sides of the triangular base: ");
    result = scanf("%lf %lf %lf", &a, &b, &c);
    if (result != 3) {
        fprintf(stderr, "Invalid input for triangle sides\n");
        return EXIT_FAILURE;
    }

    printf("Enter the height of the prism: ");
    result = scanf("%lf", &h);
    if (result != 1) {
        fprintf(stderr, "Invalid input for height\n");
        return EXIT_FAILURE;
    }

    volume = triangular_prism_volume(a, b, c, h);
    if (volume < 0) {
        fprintf(stderr, "Invalid dimensions for triangular prism\n");
        return EXIT_FAILURE;
    }

    printf("Volume of triangular prism: %.2f\n", volume);
    return EXIT_SUCCESS;
}