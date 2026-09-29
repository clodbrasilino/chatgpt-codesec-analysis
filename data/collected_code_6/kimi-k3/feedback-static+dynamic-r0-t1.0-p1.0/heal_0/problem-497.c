#include <stdio.h>
#include <math.h>
#include <errno.h>

double calculateConeSurfaceArea(double radius, double slantHeight) {
    if (radius < 0.0 || slantHeight < 0.0) {
        errno = EDOM;
        return -1.0;
    }
    return M_PI * radius * (radius + slantHeight);
}

int main(void) {
    double radius = 0.0;
    double slantHeight = 0.0;
    double surfaceArea = 0.0;

    printf("Enter the radius of the cone: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input for radius.\n");
        return 1;
    }

    printf("Enter the slant height of the cone: ");
    if (scanf("%lf", &slantHeight) != 1) {
        fprintf(stderr, "Invalid input for slant height.\n");
        return 1;
    }

    surfaceArea = calculateConeSurfaceArea(radius, slantHeight);
    if (surfaceArea < 0.0) {
        fprintf(stderr, "Invalid dimensions: radius and slant height must be non-negative.\n");
        return 1;
    }

    printf("Surface area of the cone: %.2f\n", surfaceArea);
    return 0;
}