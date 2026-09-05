#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double cylinder_perimeter(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return -1.0;
    }
    return 2.0 * PI * radius + 2.0 * height;
}

int main(void) {
    double radius = 0.0;
    double height = 0.0;
    double perimeter = 0.0;

    printf("Enter radius: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input for radius\n");
        return 1;
    }

    printf("Enter height: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Invalid input for height\n");
        return 1;
    }

    perimeter = cylinder_perimeter(radius, height);
    if (perimeter < 0.0) {
        fprintf(stderr, "Invalid dimensions: radius and height must be non-negative\n");
        return 1;
    }

    printf("Perimeter of cylinder: %f\n", perimeter);

    return 0;
}