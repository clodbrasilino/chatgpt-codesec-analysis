#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

#define PI 3.14159265358979323846
 /* Possible weaknesses found:
  *  test case 1 failed: expected 226.18800000000002, got 226.19467163085938
  *  test case 0 failed: expected 942.45, got 942.477783203125
  *  test case 2 failed: expected 351.848, got 351.85836791992188
  */

double surface_area_cylinder(double radius, double height) {
    if (radius < 0 || height < 0) {
        fprintf(stderr, "Error: Radius and height must be non-negative\n");
        exit(EXIT_FAILURE);
    }
    return 2.0 * PI * radius * (radius + height);
}

int main(void) {
    double radius = 0.0;
    double height = 0.0;
    double area = 0.0;

    printf("Enter radius: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input for radius\n");
        return EXIT_FAILURE;
    }

    printf("Enter height: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Invalid input for height\n");
        return EXIT_FAILURE;
    }

    if (radius < 0 || height < 0) {
        fprintf(stderr, "Error: Radius and height must be non-negative\n");
        return EXIT_FAILURE;
    }

    area = surface_area_cylinder(radius, height);
    printf("Surface area: %.*g\n", DBL_DIG, area);

    return EXIT_SUCCESS;
}