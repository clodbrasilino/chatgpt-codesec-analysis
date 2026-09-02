#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double cylinder_circle_area(double radius) {
    if (radius < 0) {
        return -1.0;
    }
    return M_PI * radius * radius;
}

int main(void) {
    double radius;
    char input[256];
    char *endptr;

    printf("Enter the radius of the cylinder: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    radius = strtod(input, &endptr);

    if (endptr == input || *endptr != '\n') {
        fprintf(stderr, "Invalid input. Please enter a numeric value.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0) {
        fprintf(stderr, "Radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    double area = cylinder_circle_area(radius);
    printf("The area of the top/bottom surface is: %.6f\n", area);

    return EXIT_SUCCESS;
}