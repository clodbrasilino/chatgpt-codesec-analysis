#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* Possible weaknesses found:
 *  declared here
 */
double cylinder_surface_area(double radius) {
    if (radius < 0) {
        return -1.0;
    }
    return 2.0 * M_PI * radius * radius + 2.0 * M_PI * radius;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    double radius;
    double area;
    char *endptr;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <radius> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    radius = strtod(argv[1], &endptr);
    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid radius value\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'height'
     *  'height' undeclared (first use in this function)
     */
    height = strtod(argv[2], &endptr);
    if (endptr == argv[2] || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid height value\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  too many arguments to function 'cylinder_surface_area'; expected 1, have 2
     *  use of undeclared identifier 'height'
     */
    area = cylinder_surface_area(radius, height);
    if (area < 0) {
        fprintf(stderr, "Error: Radius and height cannot be negative\n");
        return EXIT_FAILURE;
    }

    printf("%.10f\n", area);
    return EXIT_SUCCESS;
}